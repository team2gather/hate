let component = ReasonReact.statelessComponent("AppHomeRoute");

let make = (_children) => {
  ...component,
  render: self =>
  <div>
    {ReasonReact.string("Home")}   
  </div>
};