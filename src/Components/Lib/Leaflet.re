/**
 * ## React Leaflet
 * Open Source Map library for interfacing with maps; it's better than using
 * Google extremely developer-unfriendly and unstable maps
 * https://react-leaflet.js.org/
 * 
 * ## References
 * 
 * How to interop in react reason
 * https://github.com/reasonml/reason-react/blob/master/docs/interop.md
 */

type latLng = (float, float);
module Map = {
  [@bs.module "react-leaflet"] 
  external mapClass: ReasonReact.reactClass = "Map";
  
  [@bs.deriving abstract]
  type jsProps = {
    position: latLng,
    zoom: int
  };

  let make = (~center, ~zoom, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=mapClass,
      ~props=jsProps(
        ~center,
        ~zoom
      ),
      children
    );
};

module Marker = {
  [@bs.module "react-leaflet"] 
  external markerClass: ReasonReact.reactClass = "Marker";

  [@bs.deriving abstract]
  type jsProps = {
    position: latLng
  };

  let make = (~position, children) => 
    ReasonReact.wrapJsForReason(
      ~reactClass=markerClass,
      ~props=jsProps(~position),
      children
    );
};

module TileLayer = {
  [@bs.module "react-leaflet"]
  external tileLayerClass: ReasonReact.reactClass = "TileLayer";

  [@bs.deriving abstract]
  type jsProps = {
    url: string,
    opacity: Js.nullable(int),
    zIndex: Js.nullable(int)
  };

  let make = (~url, ~opacity=?, ~zIndex=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=tileLayerClass,
      ~props=jsProps(
        ~url,
        ~opacity=Js.Nullable.fromOption(opacity),
        ~zIndex=Js.Nullable.fromOption(zIndex)
      ),
      children
    );
};