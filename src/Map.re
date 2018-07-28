type state = {
    map: ref(option(GoogleMap.t)),
    meetupLocation: ref(string),
    meetupTime: ref(string),
    meetupDescription: ref(string)
};
 
type action = 
| SetMap(GoogleMap.t)
| FetchMapData
| UpdateMap(state)
;

let component = ReasonReact.reducerComponent("Map");

let make = (~mapId, ~markerId, ~db, _children) => {
    ...component,
    initialState: () => {
        map: ref(None),
        meetupLocation: ref(""),
        meetupTime: ref(""),
        meetupDescription: ref("")
    },
    didMount: self => {
        let map = GoogleMap.init(mapId, markerId, db);
        self.send(SetMap(map));
        self.send(FetchMapData);
    },
    reducer: (action, state) =>
        switch(action) {
            | SetMap(map) => {
                    state.map := Some(map);
                    ReasonReact.NoUpdate;
                }
            | FetchMapData => {
                    ReasonReact.SideEffects(self => {
                        Firestore.collection(db, "maps")
                        |. Firestore.CollectionReference.doc(mapId)
                        |. Firestore.DocumentReference.get
                        |> Js.Promise.then_(value => {
                            let data = Firestore.DocumentSnapshot.data(value);
                            self.send(UpdateMap({...self.state,
                                meetupLocation: ref(data##location),
                                meetupTime: ref(data##time),
                                meetupDescription: ref(data##description)
                            }));  
                            Js.Promise.resolve(); 
                        })
                        |> ignore
                    });
                }
            | UpdateMap(newState) => {
                ReasonReact.Update(newState);
            }
    },
    render: self => {
        Js.log(self.state);
        <div>
            <p>{ReasonReact.string(self.state.meetupLocation^)}</p>
            <p>{ReasonReact.string(self.state.meetupTime^)} </p>
            <div id="map"/>
            <p>{ReasonReact.string(self.state.meetupDescription^)}</p>
        </div> 
    }
};