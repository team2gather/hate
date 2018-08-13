open BsFirestore;

[@bs.val][@bs.scope ("document")] external getElementById : string => Dom.element = "";
[@bs.val][@bs.scope ("geolocation")] external clearWatch : int => unit = "";
[@bs.val][@bs.scope ("navigator", "geolocation")] external watchPosition : ('a, 'b) => int = "";

type markerData = {
    slackId: string,
    slackName: string,
    slackRealName: string,
    slackImageUrl: string,
    slackColor: string,
    coordinates: (float, float),
    status: string
};

type state = {
    map: ref(option(GoogleMap.t)),
    markers: ref(Js.Dict.t(GoogleMap.Marker.t)),
    meetupMarker: ref(GoogleMap.Marker.t),

    meetupLocation: string,
    meetupLocationCoordinates: (float, float),
    meetupTime: string,
    meetupDescription: string
};

type action = 
| CreateMap
| UpdateMapInfo(state)
| UpdateMapMarkers(array(markerData))
;

let component = ReasonReact.reducerComponent("Map");

let mapInfoListener = (self, mapId, dataAccessor) => {
    Firestore.collection(dataAccessor, "maps")
    |. Firestore.doc(mapId)
    |. Firestore.DocumentReference.onSnapshot((snapshot) => {
    let data = Firestore.DocumentSnapshot.data(snapshot);
        self.ReasonReact.send(UpdateMapInfo({
            ...self.ReasonReact.state,
            meetupLocation: data##location,
            meetupLocationCoordinates: (data##locationCoordinates##lat, data##locationCoordinates##lng),
            meetupTime: data##time,
            meetupDescription: data##description
        }));
    }, (error) => {
        Js.log(error);
    });
};

let mapMarkersListener = (self, mapId, markerId, dataAccessor) => {
    Firestore.collection(dataAccessor, "maps")
    |. Firestore.doc(mapId)
    |. Firestore.collection("attendees")
    |. Firestore.CollectionReference.onSnapshot((snapshot) => {
      let docs = Firestore.QuerySnapshot.docs(snapshot);
      let data = Array.map((doc) => {
        let docData = Firestore.DocumentSnapshot.data(doc);
        let marker = {
            slackId: docData##id,
            slackName: docData##name,
            slackRealName: docData##realName,
            slackImageUrl: docData##imageUrl,
            slackColor: docData##color,
            coordinates: (docData##coordinates##latitude, docData##coordinates##longitude),
            status: docData##status
        };
        marker;
      }, docs);
      self.ReasonReact.send(UpdateMapMarkers(data));
    }, (error) => {
      Js.log(error);
    });
};

let adjustMapBounds = (map, meetupMarker, peopleMarkers) => {
    let bounds = GoogleMap.LatLngBounds.instance();
    GoogleMap.LatLngBounds.extend(bounds, GoogleMap.Marker.getPosition(meetupMarker));
    Array.map(data => {
        GoogleMap.LatLngBounds.extend(bounds, GoogleMap.Marker.getPosition(data));
    }, Js.Dict.values(peopleMarkers)); 
    GoogleMap.fitBounds(map, bounds);
    GoogleMap.panToBounds(map, bounds);
}

let make = (~mapId:string, ~markerId:string, ~dataAccessor, _children) => {
    ...component,
    initialState: () => {
        map: ref(None),
        markers: ref(Js.Dict.empty()),
        meetupMarker: ref(GoogleMap.Marker.instance({
            "label": "_MEET_"
        })),
        meetupLocation: "",
        meetupLocationCoordinates: (0.0, 0.0),
        meetupTime: "",
        meetupDescription: ""
    },
    didMount: self => {
        self.send(CreateMap);

        /* GEOLOCATION LISTENER */
        let unregisterWatchPosition = watchPosition(pos => {
            Firestore.collection(dataAccessor, "maps")
            |. Firestore.doc(mapId)
            |. Firestore.collection("attendees")
            |. Firestore.doc(markerId)
            |. Firestore.DocumentReference.update({
                "coordinates": Firebase.GeoPoint.instance(pos##coords##latitude, pos##coords##longitude)
            }); 
        }, err => {
            Js.log(err);
        });

        /* DB LISTENERS */
        let mapInfoUnsubscribe = mapInfoListener(self, mapId, dataAccessor);
        let mapMarkersUnsubscribe = mapMarkersListener(self, mapId, markerId, dataAccessor);
        
        self.onUnmount(() => {
            clearWatch(unregisterWatchPosition);
            mapInfoUnsubscribe();
            mapMarkersUnsubscribe();
        });
    },
    reducer: (action, state) =>
        switch(action) {
            | CreateMap => {
                state.map := Some(GoogleMap.instance(getElementById("map")));
                let markerOverlay = GoogleMap.OverlayView.instance();
                markerOverlay##draw #= (() => {
                    let panes = GoogleMap.OverlayView.getPanes(markerOverlay);
                    panes##markerLayer##id #= "markerLayer";
                });
                GoogleMap.OverlayView.setMap(markerOverlay, state.map^);
                ReasonReact.NoUpdate;
            }
            | UpdateMapInfo(newState) => {
                ReasonReact.UpdateWithSideEffects(newState, self => {
                    switch self.state.map^ {
                        | Some(map) => {
                            GoogleMap.Marker.setOptions(self.state.meetupMarker^, {
                                "position" : GoogleMap.LatLng.instance(fst(self.state.meetupLocationCoordinates), snd(self.state.meetupLocationCoordinates)),
                                "map" : self.state.map^
                            });
                            adjustMapBounds(map, self.state.meetupMarker^, self.state.markers^);
                        }
                        | None => ();
                    };
                });
            }
            | UpdateMapMarkers(data) => {
                ReasonReact.SideEffects(self => {
                    Array.iter((mData) => {
                        let value = Js.Dict.get(self.state.markers^, mData.slackId);
                        switch value {
                            | Some(marker) => {
                                GoogleMap.Marker.setOptions(marker, {
                                    "position" : GoogleMap.LatLng.instance(fst(mData.coordinates), snd(mData.coordinates)),
                                });
                            }
                            | None => {
                                let realName = Js.String.split(" ", mData.slackRealName);
                                let shortRealName = Array.fold_left((accum, curr) => {
                                    Js.String.concat(Js.String.get(curr, 0), accum);
                                }, "", realName);

                                let newMarker = GoogleMap.Marker.instance({
                                    "label": {
                                        "text": shortRealName,
                                        "fontSize" : "12px"
                                    },
                                    "icon": { 
                                        "url" : mData.slackImageUrl,
                                        "labelOrigin": GoogleMap.Point.instance(12, -5),
                                    },
                                    "position" : GoogleMap.LatLng.instance(fst(mData.coordinates), snd(mData.coordinates)),
                                    "map" : self.state.map^
                                });
                                Js.Dict.set(self.state.markers^, mData.slackId, newMarker);
                            }
                        };
                        switch self.state.map^ {
                            | Some(map) => {
                                adjustMapBounds(map, self.state.meetupMarker^, self.state.markers^);
                            }
                            | None => ();
                        };
                    }, data);
                    
                });
            }
        
    },
    render: self => {
        <div>
            <p>{ReasonReact.string(self.state.meetupLocation)}</p>
            <p>{ReasonReact.string(self.state.meetupTime)} </p>
            <div id="map"/>
            <p>{ReasonReact.string(self.state.meetupDescription)}</p>
        </div> 
    }
};
