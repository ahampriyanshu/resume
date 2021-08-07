const { render } = require("ejs"),
express = require("express"),
date = require(__dirname + '/date.js'),
app = express(),
listItems = [],
workItems = [];

app.set('view engine', 'ejs');
app.use(express.urlencoded({extended: true}));
app.use(express.static("public"));

app.get("/", (req, res) =>  {

  const day = date.getDate();

  res.render("list", {
    listTitle: day,
    listItems: listItems
  });
});

app.get("/work", (req, res) => {
  res.render("list", {
    listTitle: "Work List",
    listItems: workItems});
});

app.post("/", (req, res) => {
  if(req.body.listSubmit === "Work"){
    workItems.push(req.body.newTodo);
    res.redirect("/work");
  }else{
    listItems.push(req.body.newTodo);
    res.redirect("/");
  }
});

app.listen(3000, () => console.log("Server is running on port 3000"));
