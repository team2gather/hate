let component = ReasonReact.statelessComponent("Home");

let make = (_children) => {
  ...component,
  render: self =>
  <div>
    {ReasonReact.string("Home")}   
  </div>
};