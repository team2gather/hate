[%bs.raw {|require('./index.css')|}];

[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

let dataAccessor = FirestoreDataAccessor.instance;
Js.log(dataAccessor);
/* dataAccessor#getMapData("HVAPqdFNWpOSh8neZWbu")
|> Js.Promise.then_(wat => {
  Js.log(wat);
  Js.Promise.resolve(wat);
}); */

ReactDOMRe.renderToElementWithId(
  <App dataAccessor=dataAccessor/>,
  "root"
);

register_service_worker();
