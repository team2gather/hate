open BsFirestore;

let config = [%bs.raw {|require('./firebase-config.json')|}];
let firebase = Firebase.initializeApp(config);
let firestore = Firebase.firestore(firebase); 

Firestore.settings(firestore, [%bs.obj {
  timestampsInSnapshots: true
}]);

let instance = {
    /* pub getMapData = (~mapId:string) => {
        Js.Promise.make((~resolve, ~reject) => {
            Firestore.collection(firestore, "maps")
            |. Firestore.doc(mapId)
            |. Firestore.DocumentReference.onSnapshot((snapshot) => {
            let data = Firestore.DocumentSnapshot.data(snapshot);
                let mapData: Interface.mapData = {
                    location: data##location,
                    coordinates: Interface.{lat: data##locationCoordinates##lat, lng: data##locationCoordinates##lng},
                    time: data##time,
                    description: data##description
                };
                resolve(. mapData);
            }, (error) => {
                Js.log(error);
            });
        });
    };
    
    pub getMarkersData = (~mapId:string) => {
        Js.Promise.make((~resolve, ~reject) => {
            Firestore.collection(firestore, "maps")
            |. Firestore.doc(mapId)
            |. Firestore.collection("attendees")
            |. Firestore.CollectionReference.onSnapshot((snapshot) => {
              let docs = Firestore.QuerySnapshot.docs(snapshot);
              let data = Array.map((doc) => {
                let docData = Firestore.DocumentSnapshot.data(doc);
                let marker: Interface.markerData = {
                    id: docData##id,
                    ign: docData##name,
                    realName: docData##realName,
                    imageUrl: docData##imageUrl,
                    color: docData##color,
                    coordinates: Interface.{lat: docData##coordinates##latitude, lng: docData##coordinates##longitude},
                    status: docData##status
                };
                marker;
              }, docs);
              resolve(. data);
            }, (error) => {
              Js.log(error);
            });
        });
    };     */

    pub subscribeToMap = (~mapId:string, ~fn:'a => unit) => {
        Firestore.collection(firestore, "maps")
        |. Firestore.doc(mapId)
        |. Firestore.DocumentReference.onSnapshot((snapshot) => {
        let data = Firestore.DocumentSnapshot.data(snapshot);
            /* self.ReasonReact.send(UpdateMapInfo({
                ...self.ReasonReact.state,
                meetupLocation: data##location,
                meetupLocationCoordinates: (data##locationCoordinates##lat, data##locationCoordinates##lng),
                meetupTime: data##time,
                meetupDescription: data##description
            })); */
            Js.log(data);
        }, (error) => {
            Js.log(error);
        });
    };

    pub updateMarkerData = (~mapId:string, ~markerId:string, ~markerData:'a) => { 
        Firestore.collection(firestore, "maps")
        |. Firestore.doc(mapId)
        |. Firestore.collection("attendees")
        |. Firestore.doc(markerId)
        |. Firestore.DocumentReference.update(markerData); 
        /* |. Firestore.DocumentReference.update({
            "coordinates": Firebase.GeoPoint.instance(pos##coords##latitude, pos##coords##longitude)
        });  */
        ();
    };
};


