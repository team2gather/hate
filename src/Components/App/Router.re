type route = 
  | RouteHome
  | RouteMap(string, string)
;

type state = {route};

type action =
  | ChangeRoute(route)
;

let mapHashToRoute = (hash: string) => {
  let params = Js.String.split("/", hash);
  switch (params) {
    | [|"", mapId, markerId|] => RouteMap(mapId, markerId)
    | _ => RouteHome
  }
};

let reducer = (action, _state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let urlToAction = (url) => url.hash |> Js.String.split("/") |> mapHashToRoute |> ChangeRoute;

let component = ReasonReact.reducerComponent("Example");

let make = (children) => {
  ...component,
  reducer,
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => {
      url |> urlToAction |> self.send
    });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self => {
    <>
      children(self)
    </>
  }
}
