type t;
[@bs.new] [@bs.scope ("google", "maps")] external newGeocoder : unit => t = "Geocoder";
[@bs.send] external geocode : (t, Js.t({..}), 'a) => unit = "geocode";
[@bs.get] external geometry : t => t = "geometry";
[@bs.get] external location : t => t = "location";

let geocoder = newGeocoder();

/* geocode(geocoder, {"address": "123 Main St"}, (result, status) => {
    let address = result[0];
}); */