type t;
[@bs.new] [@bs.scope ("google", "maps")] external newMap : (Dom.element, Js.t({..})) => t = "Map";
[@bs.val][@bs.scope ("document")] external getElementById : string => Dom.element = "";

[@bs.send]
let init = (~mapId, ~markerId, ~db) => {
    newMap(getElementById("map"), {
        "center": { "lat": -34.397, "lng": 150.644 },
        "zoom": 10
    });
}; 

