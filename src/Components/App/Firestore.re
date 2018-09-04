open BsFirestore;

let config = [%bs.raw {|require('./firebase-config.json')|}];
let firebase = Firebase.initializeApp(config);
let firestore = Firebase.firestore(firebase); 
Firestore.settings(firestore, [%bs.obj {
  timestampsInSnapshots: true
}]);

type state = {
  firestore: Firebase.t
};

let didMount = () => {
  
}

let component = ReasonReact.statelessComponent