module LatLng {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : (~lat:float, ~lng:float) => t = "LatLng";
}
module LatLngBounds {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : unit => t = "LatLngBounds";
    [@bs.send] external extend : (t, LatLng.t) => unit = "";
}
module Marker {
    type t;
    [@bs.new] [@bs.scope ("google", "maps")] external instance : Js.t({..}) => t = "Marker";
    [@bs.send] external setOptions : (t, Js.t({..})) => unit = "";
    [@bs.send] external getPosition : t => LatLng.t = "";
}

type t;
[@bs.new] [@bs.scope ("google", "maps")] external instance : (Dom.element) => t = "Map";
[@bs.send] external setCenter : (t, LatLng.t) => unit = "";
[@bs.send] external setZoom : (t, int) => unit = "";
[@bs.send] external fitBounds : (t, LatLngBounds.t) => unit = "";
[@bs.send] external panToBounds : (t, LatLngBounds.t) => unit = "";
/* 
var markers = [];//some array
var bounds = new google.maps.LatLngBounds();
for (var i = 0; i < markers.length; i++) {
 bounds.extend(markers[i].getPosition());
}
map.fitBounds(bounds); */
/* let myDict = Js.Dict.empty();
Js.Dict.set(myDict, "myKey1", {"akfj" : "sdfjk"});
Js.Dict.set(myDict, "myKey2", {"akfj" : "asdfa"});
Js.Dict.get(myDict, "myKey2"); */