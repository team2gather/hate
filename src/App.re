[%bs.raw {|require('./App.css')|}];

let config = [%bs.raw {|require('./firebase-config.json')|}];
let firebase = Firebase.initializeApp(config);
let firestore = Firebase.firestore(firebase); 
Firestore.settings(firestore, [%bs.obj {
  timestampsInSnapshots: true
}]);

type route = 
  | RouteHome
  | RouteMap(string, string)
;

type state = {route};

type action =
  | ChangeRoute(route)
;

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapHashToRoute = (hash: string) => {
  let params = Js.String.split("/", hash);
  switch (params) {
    | [|"", mapId, markerId|] => RouteMap(mapId, markerId)
    | _ => RouteHome
  }
} 

let mapUrlToRoute = (url: ReasonReact.Router.url) => {
  Js.log2("url", url);
  switch url.path {
  | [] => mapHashToRoute(url.hash)
  | _ => RouteHome
  };
}

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  reducer,
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl() |> mapUrlToRoute
  },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          self.send(ChangeRoute(url |> mapUrlToRoute))
        }),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self => {
    switch (self.state.route) {
      | RouteMap(mapId, markerId) => {
        <Map mapId markerId db=firestore/>
      }
      | RouteHome => <Home/>
    }
  }
};

