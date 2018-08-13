[%bs.raw {|require('./App.css')|}];

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

/* let mapUrlToRoute = (url: ReasonReact.Router.url) => {
  switch url.path {
  | [] => mapHashToRoute(url.hash)
  | _ => RouteHome
  };
} */

let component = ReasonReact.reducerComponent("App");

let make = (~dataAccessor, children) => {
  ...component,
  reducer,
  initialState: () => {
    route: ReasonReact.Router.dangerouslyGetInitialUrl().hash |> mapHashToRoute
  },
  /**
   * TODO: as per https://github.com/reasonml/reason-react/issues/173#issuecomment-388152222
   * we must switch to using `onMount` since this will be removed
   */
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          self.send(ChangeRoute(url.hash |> mapHashToRoute))
        }),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self => {
    switch (self.state.route) {
      | RouteMap(mapId, markerId) => {
        <Map mapId markerId dataAccessor=dataAccessor/>
      }
      | RouteHome => <Home/>
    }
  }
};

