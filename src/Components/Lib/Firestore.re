open BsFirestore;

type state = {
  firestore: Firebase.Firestore.t
};

let component = ReasonReact.reducerComponent("LibFirestore");

let make = (~config, childrenFn) => {
  ...component,
  render: (self) => childrenFn(self.state.firestore),
  initialState: () => {
    let firestore = config
      |> Firebase.initializeApp
      |> Firebase.firestore; 

    Firestore.settings(firestore, [%bs.obj {
      timestampsInSnapshots: true
    }]);

    { firestore };
  }
};