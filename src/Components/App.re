[%bs.raw {|require('./App.css')|}];

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
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
        <Map mapId markerId db=firestore/>
      }
      | RouteHome => <Home/>
    }
  }
};

