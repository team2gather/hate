[%bs.raw {|require('./App.css')|}];

let component = ReasonReact.statelessComponent("App");

let render = (self) =>
  <>
    {renderCore(self)}
    {
      if (self.props.isDevMode) {
        renderDebug(self)
      }
    }
  </>
;

let renderCore = (self) => 
  <main>
    <Router />
  </main>
;

let renderDebug = (self) => 
  <section className="debug">
    Debug Controls go here
  </section>
;

let make = (~isDevMode = true, _children) => {
  ...component,
  reducer,
  initialState,
  didMount,
  render
};

