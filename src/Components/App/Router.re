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
  