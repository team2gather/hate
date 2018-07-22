[%bs.raw {|require('./App.css')|}];

let firebase = [%bs.raw {|require('firebase/app')|}];
[%bs.raw {|require('firebase/firestore')|}]

let config = [%bs.raw {|require('./firebase-config.json')|}];
[%bs.raw {|firebase.initializeApp(config)|}];

let firestore = [%bs.raw {|firebase.firestore()|}];
[%bs.raw {|firestore.settings({timestampsInSnapshots: true})|}]
 
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
  render: self =>
    switch (self.state.route) {
      | RouteMap(mapId, markerId) => {
        <Map mapId markerId db=firestore/>
      }
      | RouteHome => <Home/>
    }
};
