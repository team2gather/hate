type state = {
    test: int
};

type action = 
| Temp;

let component = ReasonReact.reducerComponent("Map");
   
let make = (~mapId, ~markerId, ~db, _children) => {
    ...component,
    initialState: () => {test: 0},
    reducer: (action, state) =>
        switch(action) {
            | Temp => ReasonReact.Update({...state, test: state.test + 1})
    },
    render: self => {
        Js.log(db);
        let mapRef = [%bs.raw {|db.collection("maps").doc("IPzRDvavDo0pBkgFhGUu")|}];  
        <div>
            {ReasonReact.string(mapId ++ " " ++ markerId)}  
        </div>
    }
};