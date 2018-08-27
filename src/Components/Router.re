type action =
  | ChangeRoute(route)
;
let initialState = () => {
  route: PreRoute
};


let reducer = (action, _state) =>
  switch action {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
  };
  
type route = 
  | PreRoute
  | RouteHome
  | RouteMap(string, string)
;

let makeUrlHandler = (url, self) => {
  url.hash
    |> mapHashToRoute
    |> ChangeRoute
    |> self.send
};

let mountMiddleware = (app) => {
  let watcherId = app 
    |> makeUrlHandler 
    |> ReasonReact.Router.watchUrl;

  self.onUnmount(() => watcherId |> ReasonReact.Router.unwatchUrl)
};

let render = (self) => {
  switch (self.state.route) {
    | RouteMap(mapId, markerId) => {
      <Map mapId markerId db=firestore/>
    }
    | RouteHome => <Home/>
  }
}