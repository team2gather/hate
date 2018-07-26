[@bs.deriving abstract]
type x = {
  lat: float,
  lng: float
};

[@bs.deriving abstract]
type y = {
  center: x,
  zoom: int 
};

[@bs.val][@bs.scope ("document")] external getElementById : string => Dom.element = "";
type map;
[@bs.new] [@bs.scope ("google", "maps")] external makeMap : (Dom.element, Js.t({..})) => map = "Map";

let makeGoogleMap = () => {
    let map = makeMap(getElementById("map"), {
        "center": { "lat": -34.397, "lng": 150.644 },
        "zoom": 10
    });
};   

[%bs.raw {| window.makeGoogleMap = makeGoogleMap |}];

[@bs.scope "document"] [@bs.val] external createElement : (string) => Js.t('a) = "";
[@bs.scope ("document", "body")] [@bs.val] external appendChild : Js.t('a) => unit = "";

type state = {
    test: int
};

type action = 
| Temp;

let component = ReasonReact.reducerComponent("Map");

let make = (~mapId, ~markerId, ~db, _children) => {
    ...component,
    initialState: () => {test: 0},
    didMount: self => {
        let script = createElement("script");
        [%bs.raw {|
            script.async = true,
            script.src = "https://maps.googleapis.com/maps/api/js?key=AIzaSyCUs-uksty2AiVxKSQcc0wOAAm4_HBAzoQ&callback=makeGoogleMap"
        |}];
        appendChild(script); 
    },
    reducer: (action, state) =>
        switch(action) {
            | Temp => ReasonReact.Update({...state, test: state.test + 1})
    },
    render: self => {
        Firestore.collection(db, "maps")
        |. Firestore.CollectionReference.doc("IPzRDvavDo0pBkgFhGUu")
        |. Firestore.DocumentReference.get
        |> Js.Promise.then_(value => {
          let data = Firestore.DocumentSnapshot.data(value);
          Js.log(data); 
          Js.Promise.resolve(); 
        });
        <div>
            {ReasonReact.string(mapId ++ " " ++ markerId)}  
            <div id="map"/>
        </div>

        
    }
};