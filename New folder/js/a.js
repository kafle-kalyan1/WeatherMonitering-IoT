   var config = {
       apiKey: "AIzaSyByl7HRpdf2y1v7ce4fp4_72_v87uGkW44",
       authDomain: "wms-iic-iot.firebaseapp.com",
       databaseURL: "https://wms-iic-iot-default-rtdb.firebaseio.com",
       projectId: "wms-iic-iot",
       storageBucket: "wms-iic-iot.appspot.com",
       messagingSenderId: "977765006896",
       appId: "1:977765006896:web:1dd2d12f7f6d9660c677f5",
       serviceAccount: 'wms-iic-iot-firebase-adminsdk-5wp81-5b84b92e5e.jsonwms-iic-iot-firebase-adminsdk-5wp81-5b84b92e5e.json'
   };
   firebase.initializeApp(config);
   var ref = firebase.database().ref("Weather/");
   console.log("temp");

   ref.on("value", function(snapshot) {
      var data = snapshot.val();
      var temp = data.Temperature;
      var hum = data.Humidity;
      var gas = data.gas;
      let rain = data.rain;
      var tempF = data.tempF;
      console.log(data.rain);

      document.getElementById("temp").innerHTML = temp;
      document.getElementById("hum").innerHTML = hum;
      document.getElementById("gas").innerHTML = gas;
      document.getElementById("rain").innerHTML = rain;
      document.getElementById("tempF").innerHTML = tempF;
      
    });

