#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "pp";
const char* password = "pppppppp";

WebServer server(80);

#define IN1 26
#define IN2 27
#define ENA 25

void setup() {
  Serial.begin(115200);
  Serial.println("START PROGRAM");
  Serial.print("Connecting to WiFi");

int timeout = 0;

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  timeout++;

  if(timeout > 40){
    Serial.println("\nFAILED CONNECT");
    break;
  }
}

if(WiFi.status() == WL_CONNECTED){
  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());
}
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  digitalWrite(ENA, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", []() {

String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">

<link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;600&display=swap" rel="stylesheet">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">

<style>

body {
  transition: background 0.3s, color 0.3s;
  margin:0;
  font-family:'Poppins', sans-serif;
  display:flex;
  justify-content:center;
  align-items:center;
  height:100vh;
  background:#e6e9f0;
  transition:0.3s;
}

/* DARK MODE BODY */
.dark {
  background:#1e293b;
  color:#e2e8f0;
}

/* CONTAINER DARK */
.dark .container {
  background:#1f2937;
  box-shadow:
    6px 6px 12px #0f172a,
    -6px -6px 12px #374151;
}

/* STATUS CARD */
.dark .status {
  background:#111827;
  color:#e2e8f0;
}

/* BUTTON DARK */
.dark button.ctrl {
  background:#1f2937;
  box-shadow:
    4px 4px 8px #0f172a,
    -4px -4px 8px #374151;
  color:#e2e8f0;
}

.dark button.ctrl:active {
  box-shadow:
    inset 4px 4px 8px #0f172a,
    inset -4px -4px 8px #374151;
}

/* STOP BUTTON */
.dark .stop {
  color:#f87171;
}

/* THEME BUTTON */
.dark .theme-btn {
  background:#1f2937;
  box-shadow:
    3px 3px 6px #0f172a,
    -3px -3px 6px #374151;
}

/* INPUT */
.dark input {
  background:#111827;
  color:#e2e8f0;
  border:none;
}

/* TOGGLE */
.dark .toggle {
  background:#374151;
}

.dark .toggle.active {
  background:#22c55e;
}

.container {
  width:320px;
  background:#f0f3f8;
  border-radius:30px;
  padding:20px;
  box-shadow:10px 10px 20px #c8d0e7, -10px -10px 20px #fff;
  text-align:center;
  transition:0.3s;
}

.dark .container {
  background:#2a2d34;
  box-shadow:none;
}

.top-bar {
  display:flex;
  justify-content:space-between;
  align-items:center;
}

.theme-btn {
  width:35px;
  height:35px;
  border-radius:50%;
  border:none;
  background:#f0f3f8;
  box-shadow:4px 4px 8px #c8d0e7, -4px -4px 8px #fff;
  cursor:pointer;
}

.dark .theme-btn {
  background:#1e293b;
  color:white;
}

.status {
  background:#2a2d34;
  color:white;
  padding:20px;
  border-radius:20px;
  margin:20px 0;
}

.controls {
  display:flex;
  justify-content:space-around;
}

button.ctrl {
  width:70px;
  height:70px;
  border:none;
  border-radius:20px;
  background:#f0f3f8;
  box-shadow:6px 6px 12px #c8d0e7, -6px -6px 12px #fff;
  font-size:20px;
}

button.ctrl:active {
  box-shadow:inset 4px 4px 8px #c8d0e7, inset -4px -4px 8px #fff;
}

.stop { color:red; }

.schedule {
  margin-top:20px;
  padding:10px;
}

input {
  margin:5px;
}

.toggle {
  width:40px;
  height:20px;
  background:#ccc;
  border-radius:20px;
  position:relative;
  cursor:pointer;
}

.toggle::after {
  content:"";
  width:18px;
  height:18px;
  background:white;
  position:absolute;
  top:1px;
  left:1px;
  border-radius:50%;
  transition:0.3s;
}

.toggle.active {
  background:#22c55e;
}

.toggle.active::after {
  left:20px;
}

</style>
</head>

<body>

<div class="container">

<div class="top-bar">
  <h3>Smart Curtain</h3>
  <button class="theme-btn" onclick="toggleTheme()">
    <i id="themeIcon" class="fas fa-moon"></i>
  </button>
</div>

<div class="status">
  <div id="status">STOP</div>
</div>

<div class="controls">
  <button class="ctrl" onclick="control('maju')"><i class="fas fa-chevron-up"></i></button>
  <button class="ctrl stop" onclick="control('stop')"><i class="fas fa-stop"></i></button>
  <button class="ctrl" onclick="control('mundur')"><i class="fas fa-chevron-down"></i></button>
</div>

<div class="schedule">
  <h4>Schedule</h4>
  <input type="time" id="openTime">
  <input type="time" id="closeTime">
  <div id="toggle" class="toggle" onclick="toggleSchedule()"></div>
</div>

</div>

<script>

let scheduleActive = false;
let lastRun = "";

function control(cmd){
  fetch('/' + cmd);

  let status = document.getElementById("status");

  if(cmd=="maju") status.innerText="MEMBUKA";
  else if(cmd=="mundur") status.innerText="MENUTUP";
  else status.innerText="STOP";
}

function toggleTheme(){
  document.body.classList.toggle("dark");

  let icon = document.getElementById("themeIcon");
  if(document.body.classList.contains("dark")){
    icon.className = "fas fa-sun";
  } else {
    icon.className = "fas fa-moon";
  }
}

function toggleSchedule(){
  let toggle = document.getElementById("toggle");
  toggle.classList.toggle("active");
  scheduleActive = toggle.classList.contains("active");
}

setInterval(()=>{
  if(!scheduleActive) return;

  let now = new Date();
  let time = now.getHours().toString().padStart(2,'0') + ":" + now.getMinutes().toString().padStart(2,'0');

  let open = document.getElementById("openTime").value;
  let close = document.getElementById("closeTime").value;

  if(time == open && lastRun != open){
    control('maju');
    lastRun = open;
  }

  if(time == close && lastRun != close){
    control('mundur');
    lastRun = close;
  }

},1000);

</script>

</body>
</html>
)rawliteral";

    server.send(200, "text/html", html);
  });

  server.on("/maju", []() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    server.send(200, "text/plain", "OK");
  });

  server.on("/mundur", []() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    server.send(200, "text/plain", "OK");
  });

  server.on("/stop", []() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}