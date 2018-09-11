/**
 * https://tomchentw.github.io/react-google-maps/
 */

 /**
  * https://tomchentw.github.io/react-google-maps/#googlemap
  */
 module GoogleMap = {
  [@bs.module "react-google-maps"] 
  external googleMapClass: ReasonReact.reactClass = "GoogleMap";

  [@bs.deriving abstract]
  type jsProps = {
    defaultExtraMapTypes: arrayOf[],
    defaultCenter: any,
    defaultClickableIcons: bool,
    defaultHeading: number,
    defaultMapTypeId: any,
    defaultOptions: any,
    defaultStreetView: any,
    defaultTilt: number,
    defaultZoom: number,
    center: any,
    clickableIcons: bool,
    heading: number,
    mapTypeId: any,
    options: any,
    streetView: any,
    tilt: number,
    zoom: number,
    onDblClick: func,
    onDragEnd: func,
    onDragStart: func,
    onMapTypeIdChanged: func,
    onMouseMove: func,
    onMouseOut: func,
    onMouseOver: func,
    onRightClick: func,
    onTilesLoaded: func,
    onBoundsChanged: func,
    onCenterChanged: func,
    onClick: func,
    onDrag: func,
    onHeadingChanged: func,
    onIdle: func,
    onProjectionChanged: func,
    onResize: func,
    onTiltChanged: func,
    onZoomChanged: func,
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