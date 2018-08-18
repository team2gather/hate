module LatLng {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : (~lat:float, ~lng:float) => t = "LatLng";
};
module LatLngBounds {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : unit => t = "LatLngBounds";
    [@bs.send] external extend : (t, LatLng.t) => unit = "";
};
module Marker {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : Js.t({..}) => t = "Marker";
    [@bs.send] external setOptions : (t, Js.t({..})) => unit = "";
    [@bs.send] external getPosition : t => LatLng.t = "";
};
module OverlayView {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : unit => 'a = "OverlayView";
    [@bs.send] external setMap : (t, 'a) => unit = "";
    [@bs.send] external getPanes : t => 'a = "";
};
module Point {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : (~x:int, ~y:int) => t = "Point";
};
type t;
[@bs.new] [@bs.scope ("google", "maps")] external instance : (Dom.element) => t = "Map";
[@bs.send] external setCenter : (t, LatLng.t) => unit = "";
[@bs.send] external setZoom : (t, int) => unit = "";
[@bs.send] external fitBounds : (t, LatLngBounds.t) => unit = "";
[@bs.send] external panToBounds : (t, LatLngBounds.t) => unit = "";
