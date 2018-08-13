type latLng = {
   lat: float,
   lng: float
};

type mapData = {
  location: string,
  coordinates: latLng,
  time: string,
  description: string
};

type markerData = {
  id: string,
  ign: string,
  realName: string,
  imageUrl: string,
  color: string,
  coordinates: latLng,
  status: string,
};


type markerUpdate('a) = 'a;

type dataAccessor = {.
    /* getMapData: (~mapId:string) => Js.Promise.t(mapData), */
    /* getMarkersData: (~mapId:string) => Js.Promise.t(array(markerData)), */
    /* updateMarkerData: (~mapId:string, ~markerId:string, ~markerData:{.. }) => string */
};

module type DataAccessorInstance = {
  let instance: dataAccessor;
};


