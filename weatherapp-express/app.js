const express = require("express"),
  https = require("https"),
  app = express();

app.use(express.urlencoded({ extended: true }));

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

app.post("/", (req, res) => {
  const query = req.body.cityName,
    apiKey = "*****************",
    unit = "metric",
    url =
      "https://api.openweathermap.org/data/2.5/weather?q=" +
      query +
      "&appid=" +
      apiKey +
      "&units=" +
      unit;

https.get(url, (response) => {
    if (parseInt(response.statusCode) !== 200) {
      res.send(`<h1 style=" text-align: center; position: absolute;left: 50%;top: 50%;-webkit-transform: translate(-50%, -50%);transform: translate(-50%, -50%);
      font-family: Lucida Console; color:red">${query} isn't a city</h1>`);
      return;
    }
    response.on("data", (data) => {
      const weatherData = JSON.parse(data),
      temp = weatherData.main.temp,
      desc = weatherData.weather[0].description,
      icon = weatherData.weather[0].icon,
      iconUrl = "http://openweathermap.org/img/wn/" + icon + "@2x.png";
      res.write(`<div style=" text-align: center; position: absolute;left: 50%;top: 50%;-webkit-transform: translate(-50%, -50%);transform: translate(-50%, -50%);
      font-family: Lucida Console;"><h1>The temperature in ${query} is  ${temp} Celcius<h1>
        <h1 style="">Weather Status :  ${desc} <h1>
        <img src=" ${iconUrl} " /><div>
        `);
      res.send();
    });
  });
});

app.listen(3000, () => console.log("Server is running on port 3000"));
