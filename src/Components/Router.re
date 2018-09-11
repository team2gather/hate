type action =
  | ChangeRoute(route)
;
let initialState = () => {
  route: RouteHome
};

let reducer = (action, _state) =>
  switch action {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
  };
  
type route = 
  | RouteHome
  | RouteMap(string, string)
;

let makeUrlHandler = (url, self) => {
  url.hash
    |> mapHashToRoute
    |> ChangeRoute
    |> self.send
};

let didMount = (app) => {
  let watcherId = app 
    |> makeUrlHandler 
    |> ReasonReact.Router.watchUrl;

  self.onUnmount(() => watcherId |> ReasonReact.Router.unwatchUrl)
};

let render = (self) => {
  switch (self.state.route) {
    | RouteMap(mapId, markerId) => {
      <MapRoute mapId markerId db=firestore />
    }
    | RouteHome => <HomeRoute />
  }
}

let component = ReasonReact.reducerComponent("Router");

let make = () => {
  ...component,
  render,
  didMount,
  reducer,
  initialState
}