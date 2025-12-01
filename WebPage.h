String WebPage = R"HTML5(<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Signal Generator</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!--  PNG favicon image, encoded as base64 -> https://elmah.io/tools/base64-image-encoder/ -->
  <link rel="shortcut icon" type="image/png" sizes="16x16" href="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAQAAAC1+jfqAAAABGdBTUEAALGPC/xhBQAAAAlwSFlzAAAuIwAALiMBeKU/dgAAAAd0SU1FB+cBFRcAJyFRDxkAAAAZdEVYdENvbW1lbnQAQ3JlYXRlZCB3aXRoIEdJTVBXgQ4XAAAA3ElEQVQoz4WRP0tCcRSGH34u0ReIxoKQwBovTQ1iGPgxwqFdcg/nvoHQ3DdoqqFJh8ylMXFsMCSoIa+Pg97rn3vDZznDeTnnvOfFsgP/Y2CZpB07yZUwr13PLfmYowgAQy7Y55QqPTKo3nrsyJFFr5xuTEA/DbZVbUvm4gB9pkQAnAHvGxsCdNnhAIBD9nhLW01uAGJrXqcDG0YLu2Pxbn7DKg/ih6o98TmxueQEeAWgQ6CU2Fzy56UVf/yyaCuxuc6T2LDu7sJwRhB7b8EjX9JH5WT57e9KWFvingFTFG1S956a3gAAAABJRU5ErkJggg==" />
<style>
  /* once you open a style tag, CSS comment rules apply */
  html {
    width: 100% !important;
    height: 100% !important;
    font-family: 'Segoe UI', Arial, sans-serif;
    display: inline-block;
    color: #1a4d7a;
    margin: 0;
  }
  div, pre {
    margin: 0;
  }
  p, form {
    margin: 0;
  }
  button, .nice-input, #head, .preset-button {
    border-radius: 0.5em;
  }
  .controller {
    margin: 1.75em auto auto auto;
    width: 96%;
  }
  label {
    display: none;
  }
  .right {
    text-align: right;
    padding-right: 0.25em;
    float: right;
  }
  #version {
    font-size: 80%;
  }
  #head {
    background: linear-gradient(135deg, #1a4d7a 0%, #2563a8 100%);
    padding: 0.4em 0 0.4em 0.4em;
    color: white;
    font-size: 2em;
    font-weight: bold;
    margin-top: 1.5em;
    z-index: 100;
    box-shadow: 0 4px 8px rgba(26, 77, 122, 0.3);
  }
  #frequencyVAL, #WaveModeVAL, #DOWN, #UP, #status, #send-button,
   #power, #waves, #waver, #wavet, .set-button {
    cursor: pointer;
  }
  .button, .step-button, .nice-input, .set-button, #status, #send-button  {
    background: linear-gradient(135deg, #1a4d7a 0%, #2563a8 100%);
    border: none;
    color: white;
    padding: 0.3em 0.4em;
    font-size: 2.5em;
    font-weight: bold;
    box-shadow: 0 4px 6px rgba(26, 77, 122, 0.3);
    transition: all 0.3s ease;
  }
  .button, .step-button, .nice-input, .set-button, #status, #send-button {
    margin: 0.175em auto
  }
  .button:hover, .step-button:hover, .set-button:hover, #status:hover {
    background: linear-gradient(135deg, #2563a8 0%, #3a7bc8 100%);
    transform: translateY(-2px);
    box-shadow: 0 6px 12px rgba(26, 77, 122, 0.4);
  }
  .button:active, .step-button:active, .set-button:active, #status:active {
    background: linear-gradient(135deg, #0f3a5f 0%, #1a4d7a 100%);
    color: white;
    transform: translateY(1px);
    box-shadow: 0 2px 4px rgba(26, 77, 122, 0.3);
  }
  .nice-input:hover {
    background: linear-gradient(135deg, #2563a8 0%, #3a7bc8 100%);
    transform: translateY(-1px);
  }
  .nice-input:active, .nice-input:focus {
    background: white;
    color: #1a4d7a;
    outline: 3px solid #2563a8;
  }
  .button {
    width: 100%;
  }
  .step-button {
    width: 40%;
    text-align: center;
  }
  #UP {
    float: right;
  }
  #status {
    width: 16%;
    margin-left: 1.2%;
  }
  .nice-input {
    width: 74%;
  }
  .set-button, #send-button {
    width: 20%;
    float: right;
    padding: 0.1em 0;
  }
  #live-values {
    column-count: 2;
    font-size: 1.5em;
    font-weight: bold;
    margin: 0.15em 0;
    padding: 0 0.05em;
  }
  #frequencyVAL {
    padding-left: 0.15em;
  }
  #inputGrid {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 0.5em;
    margin: 0.5em 0;
  }
  #inputGrid > div {
    width: 100%;
  }
  #inputGrid .nice-input {
    width: 70%;
  }
  #inputGrid .set-button {
    width: 20%;
  }
  #waveforms {
    padding-right: 0.15em;
    display: flex;
    justify-content: space-between;
    gap: 0.2em;
  }
  #waveforms > div {
    flex: 1;
  }
  #waves, #waver, #wavet, #wavesaw {
    height: 1.7em;
    font-size: 400%;
    width: 100%;
  }
  #power {
	opacity: 0.25;
    z-index: 100;
    position: fixed;
    top: 5px;
    right: 5px;
    border-radius: 16px;
  }

  #power:active {
    background-color: #1a4d7a;
  }
  #power:hover {
	opacity: 1;
  }
  #credit, #credit a {
    position: fixed;
    font-size: 0.8em;
    color: #1a4d7a;
    bottom: 0.5em;
    right: 0.25em;
  }
  #InfoDIV {
	font-family: Consolas, ProFontWindows,  'Lucida Console', 'Courier New', monospace;
    font-size: 120%;
	color: #1a4d7a;
    position: fixed;
    padding: 0;
    left: 9%;
    top: 0.5em;
    width: 85%;
    height: 5em;
/*    background-color: red;*/
    column-count: 3; /* Thank God for CSS3 */
    z-index: -1;
  }
  #waveCanvas {
    display: block;
    margin: 0.5em auto;
    border: 3px solid #1a4d7a;
    border-radius: 0.5em;
    background: linear-gradient(to bottom, #ffffff 0%, #f5f5f5 100%);
    cursor: crosshair;
    box-shadow: 0 8px 16px rgba(26, 77, 122, 0.2);
  }
  #waveCanvasContainer {
    position: relative;
    width: 100%;
  }
  #waveTooltip {
    position: absolute;
    background-color: rgba(26, 77, 122, 0.95);
    color: white;
    padding: 0.5em;
    border-radius: 0.25em;
    font-size: 0.9em;
    pointer-events: none;
    display: none;
    z-index: 1000;
    white-space: nowrap;
  }
  #fftCanvas {
    display: block;
    margin: 0.5em auto;
    border: 3px solid #1a4d7a;
    border-radius: 0.5em;
    background: linear-gradient(to bottom, #ffffff 0%, #f5f5f5 100%);
    box-shadow: 0 8px 16px rgba(26, 77, 122, 0.2);
  }
  #fftCanvasContainer {
    position: relative;
    width: 100%;
    margin-top: 1em;
    display: none;  /* Hidden by default - only show in FFT-only mode */
  }
  #fftTitle {
    text-align: center;
    font-size: 1.5em;
    font-weight: bold;
    color: #1a4d7a;
    margin: 0.5em 0 0.25em 0;
  }
  #downloadCSV {
    background: linear-gradient(135deg, #28a745 0%, #34c759 100%);
    color: white;
    border: none;
    padding: 0.4em 0.8em;
    font-size: 0.9em;
    font-weight: bold;
    border-radius: 0.4em;
    cursor: pointer;
    margin-left: 1em;
    box-shadow: 0 3px 6px rgba(40, 167, 69, 0.3);
    transition: all 0.3s ease;
  }
  #downloadCSV:hover {
    background: linear-gradient(135deg, #34c759 0%, #48d26a 100%);
    transform: translateY(-2px);
    box-shadow: 0 5px 10px rgba(40, 167, 69, 0.4);
  }
  #downloadCSV:active {
    transform: translateY(1px);
  }
  #viewToggle {
    position: fixed;
    top: 5px;
    left: 5px;
    background: linear-gradient(135deg, #1a4d7a 0%, #2563a8 100%);
    color: white;
    border: none;
    padding: 0.5em 1em;
    font-size: 1em;
    font-weight: bold;
    border-radius: 0.5em;
    cursor: pointer;
    z-index: 200;
    box-shadow: 0 4px 8px rgba(26, 77, 122, 0.3);
    transition: all 0.3s ease;
  }
  #viewToggle:hover {
    background: linear-gradient(135deg, #2563a8 0%, #3a7bc8 100%);
    transform: translateY(-2px);
    box-shadow: 0 6px 12px rgba(26, 77, 122, 0.4);
  }
  #viewToggle:active {
    transform: translateY(1px);
  }
  .hidden {
    display: none !important;
  }
  #webConsole, #send-button {
    margin: 0;
    font-size: 90%;
    background-color: white;
    color: white;
    line-height: 1.4em; /* omfg! someone please fix this CSS! lol */
  }
  #webConsole {
  }
  #send-button {
    margin-right: 0.2em;
  }
  #send-button:hover {
    background-color: #1a4d7a;
    color: white;
  }
  #send-button:active {
    background-color: white;
    color: #1a4d7a;
  }
  /*
  If you add this stuff, your CSS is "Responsive", like magic..
  Crucially, we define the stuff for *any* browser *first*, _then_ /add/ capabilities.
  Or just move stuff about, like this..
                                                                */
  @media screen and (min-width: 1000px) and (max-width: 2048px) {
    .controller {
      width: 50%;
      margin: 1em auto auto auto;
    }
    #head {
      margin-top: 0;
    }
    #power {
      right: 0.24em;
    }
    #power {
      opacity: 0.5;
    }
    #InfoDIV {
      column-count: 1;
      height: auto;
/*      width: auto;*/
      max-width: 25%;
      padding: 0 1em 1em 0.2em;
      left: 3em;
      top: 5px;
      font-size: 120%;
    }
    .nice-input {
      width: 75%;
     }
  }
</style>
</head>
<body>
  <button id="viewToggle" onclick="toggleView()" title="Switch between Signal Generator and FFT Analyzer views">Show FFT Only</button>
  <div class="controller" id="controllerDiv"><!-- You can switch out {tokens} for live data at page-load -->
    <div id="head">
      <form onsubmit="return false;"><div><input id="webConsole" class="nice-input" onfocus="if (this.value=='Command') this.value = ''" onblur="if (this.value=='') this.value = 'Command'" type="text" value="Command" title="Enter commands just as you would in a serial console.
When a response has been received, this input will reset."><button onclick="sendCommand()" id="send-button" type="submit" title="Click here to send the command. (or hit &lt;enter&gt; from the input)">Send</button></div></form>
    </div>
    <div id="live-values">
      <p id="frequencyVAL" onclick="getFrequency()" title="Click here to update with the current frequency.">Frequency: <span id="FreqValue"></span></p>
      <p id="WaveModeVAL" onclick="getWaveForm()" class="right" title="Click here to update with the current waveform.">Wave: <span id="WaveForm"></span></p>
    </div>
    <div>
      <label for="DOWN">DOWN</label>
      <button id="DOWN" onclick="setDOWN()" class="step-button" title="Move frequency DOWN one step.">DOWN</button>
      <label for="status">info</label>
      <button id="status" onclick="getStatus()" title="get current status info
(which may have been altered from elsewhere)">?</button>
      <label for="UP">UP</label>
      <button id="UP" onclick="setUP()" class="step-button" title="Move frequency UP one step.">UP</button>
    </div>
    <div id="inputGrid">
      <div>
        <!-- we create actual form elements so <enter> can set values -->
        <form onsubmit="return false;">
          <label for="frequency">Frequency</label>
          <input id="frequency" class="nice-input" name="frequency" onfocus="if (this.value=='Frequency') this.value = ''" onblur="if (this.value=='') this.value = 'Frequency'" type="text" value="Frequency" title="Input your desired frequency here, in Hz, kHz(k), or MHz(m). e.g. 2.34m">
          <button onclick="setFreqency()" class="set-button" type="submit" title="Click here to set the frequency.
(or hit &lt;enter&gt; from the input)">set</button>
        </form>
      </div>
      <div>
        <form onsubmit="return false;">
          <label for="step">Step Size</label>
          <input id="step" class="nice-input" name="step" onfocus="if (this.value=='Step Size') this.value = ''" onblur="if (this.value=='') this.value = 'Step Size'" type="text" value="Step Size" title="Enter the value of your desired step size, in Hz, kHz(k), or MHz(m). e.g. 1k">
          <button onclick="setStep()" class="set-button" title="Click here to set the frequency step size.
(or hit &lt;enter&gt; from the input)">set</button>
        </form>
      </div>
      <div>
        <form onsubmit="return false;">
          <label for="pulse">Pulse Width (%)</label>
          <input id="pulse" class="nice-input" name="pulse" onfocus="if (this.value=='Pulse Width (%)') this.value = ''" onblur="if (this.value=='') this.value = 'Pulse Width (%)'" type="text" value="Pulse Width (%)" title="enter the value for the pulse width percent (0-100).
note: this also sets sawtooth angle in the triangle generator">
          <button onclick="setPulseWidth()" class="set-button" title="Click here to set the pulse width.
(or hit &lt;enter&gt; from the input)">set</button>
        </form>
      </div>
      <div>
        <form onsubmit="return false;">
          <label for="amplitude">Amplitude (Volts)</label>
          <input id="amplitude" class="nice-input" name="amplitude" onfocus="if (this.value=='Amplitude (0.0-3.3V)') this.value = ''" onblur="if (this.value=='') this.value = 'Amplitude (0.0-3.3V)'" type="text" value="Amplitude (0.0-3.3V)" title="enter the amplitude in volts (0.0-3.3V) for sine, triangle and sawtooth waves.
note: square wave is always full amplitude">
          <button onclick="setAmplitude()" class="set-button" title="Click here to set the amplitude in volts.
(or hit &lt;enter&gt; from the input)">set</button>
        </form>
      </div>
    </div>
    <div id="waveforms">
      <div>
        <label for="waver">Square Wave</label>
        <button id="waver" onclick="setSquare()" class="button" title="Select Square/Rectangle Wave.">&SquareIntersection;</button><!--&EmptySmallSquare;-->
      </div>
      <div>
        <label for="waves">Sine Wave</label>
        <button id="waves" onclick="setSine()" class="button" title="Select Sine Wave.">&#8767;</button>
      </div>
      <div>
        <label for="wavet">Triangle Wave</label>
        <button id="wavet" onclick="setTriangle()" class="button" title="Select Triangle wave (50% pulse width).">&bigtriangleup;</button><!-- &utri; -->
      </div>
      <div>
        <label for="wavesaw">Sawtooth</label>
        <button id="wavesaw" onclick="setSaw()" class="button" title="Select Sawtooth wave (1% pulse width - sharp rise, slow fall).">&#9582;</button>
      </div>
    </div>
    <div id="waveCanvasContainer">
      <canvas id="waveCanvas" width="1200" height="400" title="Live waveform preview - hover for details"></canvas>
      <div id="waveTooltip"></div>
    </div>
  </div>
  <div id="fftCanvasContainer">
    <div id="fftTitle">FFT Spectrum Analyzer (Input Signal) <button id="downloadCSV" onclick="downloadFFTCSV()" title="Download FFT data as CSV file">&#x2B73; Download CSV</button></div>
    <canvas id="fftCanvas" width="1200" height="300" title="FFT frequency spectrum of ADC input"></canvas>
  </div>
  <div id="InfoDIV" title="Information appears here.
Click the '?' button to put the current signal settings here."></div>
  <img alt="reboot button" id="power" onclick="rebootDevice()" title="Reboot your ESP32 device." alt="reboot link" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH5wEUBQsAwLFzwgAAAS9QTFRFAAAAnL6djYuN2tnatLW0WKhbcZlyfreAh5mHX7BiYLFiYLJjQ5NGhJ2FU6NVWo9chbeGfrmAZJtmX7Bifrh/TahRT6lTh7yIiLyJS61PTK1QfLZ+S65PZbJoZahnh7yIT6ZSUK9UTaNQTqdRbrRxUa1VjL2OTaVQkr+Tkr+Uk7+Uk8CUVahYWrBdUq9WUqpVT61TV6daW69eUqpVX7FiZrJoUq5VTapRTqpSTK9QZLNnabJrVKlXTqpSTapRSqpOSqdOX65hWbFdWLFbU61XUqxVV61aWKdaWKdbWq9dS65PWrJdV7FaTq1SWLFbTK9QTa9RTa1RTK5QVK5XUq5VUbBVY7BmZLJnX7BhUK5UVK1XTK1QTq1RUrBVTK9QZLJnTK9QT61TTK9QTa1RTa9RV8m/+AAAAGJ0Uk5TAAEFBggKCgoKCwsLFBQWGx0eHyInKioqKjAwMTw9UVJTU1dXWlxcZmdnZ2dqbHN3fX+DhoaNjpCRmZmZm56ipKqrrLW4u7u8vL/BxcbJy8zN1trf4+bn7/D09PX4+/z8/v6FBQ+kAAABZ0lEQVQYGZXBh1YTUQBF0UtvgjSx0JUyZFBAFMVC7y2EpnQ4+P/f4H2TGDMRXIu99UivT07e6D9aL+GyVQ/rx/r1sAiLdK9XPRVShEVSRc9LpTUswF6dxrAx1e3BQoNKNG5hg4qxWIPYVqP+WiMYUAbLaIBgTUUTBJtSjMXSJsGEClrOsdlqKcIiqXoWO29R3mdsRZbBMrIV7JMSVWfA6RNZhEWyp6fAWZWCPmxGQYzFCmawPgUfsW4FI9iIgm7sg4Il4FqJTqxTiWtgScE2kFXe1NXVlPKywLaCHSCrgspKFWSBHQXLwA/94yewrOAL1qYybdhXBUPYW5V5hw0paL4AjuqVUn8EXDQrMYdNK2Uam1Peszvg16hKjGJ3XSr4jt1Mquj9DfZNf9QcEuSGa2W1wzmCwxoVdRyTuN3dWN+9JXHcoRLPDyhz8EIpTYukLDapXO8qRau9uk/7+Px+Lrc/P96uR/gNGtKGbTbWpfEAAAAASUVORK5CYII=" />
  <div id="credit"><a href="https://corz.org/" target="_blank">from corz.org</a></div>

<script>

// When you *do* stuff, the info DIVs update with the full wave information after this time (ms)..
var updateDelay = 777;

// When you send commands with the console interface, the info DIV updates with the response after
// this time, then again with the current status in 2 * this time.

// There is no way back. If you really must read the title again, refresh the page.
var goneConsole = false;


// Waveform drawing variables
var currentWaveMode = 'r';
var currentFrequency = 1000;
var currentPulse = 50;
var currentAmplitude = 3.3;

// Draw waveform on canvas
function drawWaveform() {
  var canvas = document.getElementById('waveCanvas');
  if (!canvas) return;
  
  var ctx = canvas.getContext('2d');
  var width = canvas.width;
  var height = canvas.height;
  var centerY = height / 2;
  var padding = 20;
  var drawWidth = width - 2 * padding;
  var drawHeight = height - 2 * padding;
  
  // Clear canvas
  ctx.fillStyle = '#f0f0f0';
  ctx.fillRect(0, 0, width, height);
  
  // Draw grid
  ctx.strokeStyle = '#d0d0d0';
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(padding, centerY);
  ctx.lineTo(width - padding, centerY);
  ctx.stroke();
  
  // Draw waveform
  ctx.strokeStyle = '#1a4d7a';
  ctx.lineWidth = 2;
  ctx.beginPath();
  
  var cycles = 2; // Show 2 complete cycles
  var samples = 200;
  
  for (var i = 0; i <= samples; i++) {
    var x = padding + (i / samples) * drawWidth;
    var phase = (i / samples) * cycles * 2 * Math.PI;
    var y = centerY;
    
    // Calculate amplitude scaling (0-3.3V, square is always full)
    var ampScale = (currentWaveMode === 'r') ? 1.0 : (currentAmplitude / 3.3);
    
    switch(currentWaveMode) {
      case 's': // Sine
        y = centerY - Math.sin(phase) * (drawHeight / 2) * ampScale;
        break;
        
      case 'r': // Square/Rectangle
        var pulsePoint = currentPulse / 100.0;
        var phaseNorm = (phase / (2 * Math.PI)) % 1.0;
        y = (phaseNorm < pulsePoint) ? 
            (centerY - drawHeight / 2) : 
            (centerY + drawHeight / 2);
        break;
        
      case 't': // Triangle
        var pulsePoint = currentPulse / 100.0;
        var phaseNorm = (phase / (2 * Math.PI)) % 1.0;
        if (phaseNorm < pulsePoint) {
          // Rising edge
          y = centerY + drawHeight / 2 - (phaseNorm / pulsePoint) * drawHeight * ampScale;
        } else {
          // Falling edge
          y = centerY - drawHeight / 2 + ((phaseNorm - pulsePoint) / (1.0 - pulsePoint)) * drawHeight * ampScale;
        }
        break;
        
      case 'w': // Sawtooth (1% pulse)
        var pulsePoint = 0.01;
        var phaseNorm = (phase / (2 * Math.PI)) % 1.0;
        if (phaseNorm < pulsePoint) {
          // Quick rising edge
          y = centerY + drawHeight / 2 - (phaseNorm / pulsePoint) * drawHeight * ampScale;
        } else {
          // Slow falling edge
          y = centerY - drawHeight / 2 + ((phaseNorm - pulsePoint) / (1.0 - pulsePoint)) * drawHeight * ampScale;
        }
        break;
    }
    
    if (i === 0) {
      ctx.moveTo(x, y);
    } else {
      ctx.lineTo(x, y);
    }
  }
  
  ctx.stroke();
  
  // Draw labels
  ctx.fillStyle = '#1a4d7a';
  ctx.font = '12px Tahoma';
  var modeNames = {'s': 'Sine', 'r': 'Square', 't': 'Triangle', 'w': 'Sawtooth'};
  var label = modeNames[currentWaveMode] + ' - ' + formatFrequency(currentFrequency);
  if (currentWaveMode !== 'r' && currentWaveMode !== 's') {
    label += ' - PWM: ' + currentPulse + '%';
  }
  if (currentWaveMode !== 'r') {
    label += ' - Amp: ' + currentAmplitude.toFixed(1) + 'V';
  }
  ctx.fillText(label, padding, 15);
}

// Format frequency for display
function formatFrequency(freq) {
  if (freq >= 1000000) {
    return (freq / 1000000).toFixed(2) + 'MHz';
  } else if (freq >= 1000) {
    return (freq / 1000).toFixed(2) + 'kHz';
  } else {
    return freq + 'Hz';
  }
}

// Get waveform parameters from ESP32
function updateWaveformData() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      try {
        var data = JSON.parse(this.responseText);
        currentWaveMode = data.mode || currentWaveMode;
        currentFrequency = data.frequency || currentFrequency;
        currentPulse = data.pulse || currentPulse;
        currentAmplitude = data.amplitude || currentAmplitude;
        drawWaveform();
      } catch(e) {
        // If JSON fails, parse text response
        var text = this.responseText;
        if (text.includes('Sine')) currentWaveMode = 's';
        else if (text.includes('Square') || text.includes('Rectangle')) currentWaveMode = 'r';
        else if (text.includes('Triangle')) currentWaveMode = 't';
        else if (text.includes('Sawtooth')) currentWaveMode = 'w';
        drawWaveform();
      }
    }
  };
  AJAX.open("GET", "getWaveData", true);
  AJAX.send();
}

// Draw FFT spectrum
function drawFFT(fftData) {
  var canvas = document.getElementById('fftCanvas');
  if (!canvas) return;
  
  var ctx = canvas.getContext('2d');
  var width = canvas.width;
  var height = canvas.height;
  var padding = 40;
  var drawWidth = width - 2 * padding;
  var drawHeight = height - 2 * padding;
  
  // Clear canvas
  ctx.fillStyle = '#f5f5f5';
  ctx.fillRect(0, 0, width, height);
  
  // Draw grid lines
  ctx.strokeStyle = '#d0d0d0';
  ctx.lineWidth = 1;
  for (var i = 0; i <= 4; i++) {
    var y = padding + (i * drawHeight / 4);
    ctx.beginPath();
    ctx.moveTo(padding, y);
    ctx.lineTo(width - padding, y);
    ctx.stroke();
  }
  
  // Draw labels
  ctx.fillStyle = '#1a4d7a';
  ctx.font = '14px Segoe UI';
  ctx.textAlign = 'left';
  ctx.fillText('Fs=' + (fftData.fs / 1000) + 'kHz', padding, 20);
  ctx.fillText('N=' + fftData.n, padding + 100, 20);
  ctx.fillText('Fp=' + fftData.fp + 'Hz', padding + 200, 20);
  
  // Draw frequency spectrum bars
  var bins = fftData.bins;
  var barWidth = drawWidth / bins.length;
  
  ctx.fillStyle = '#1a4d7a';
  for (var i = 0; i < bins.length; i++) {
    var magnitude = bins[i] / 100.0; // normalized 0-1
    var barHeight = magnitude * drawHeight;
    var x = padding + (i * barWidth);
    var y = padding + drawHeight - barHeight;
    
    ctx.fillRect(x, y, barWidth - 1, barHeight);
  }
  
  // Draw frequency axis labels
  ctx.textAlign = 'center';
  ctx.font = '12px Segoe UI';
  var maxFreq = fftData.fs / 2;
  for (var i = 0; i <= 4; i++) {
    var freq = (i * maxFreq / 4);
    var x = padding + (i * drawWidth / 4);
    var label = freq >= 1000 ? (freq / 1000).toFixed(1) + 'k' : freq.toFixed(0);
    ctx.fillText(label + 'Hz', x, height - 5);
  }
}

// Get FFT data from ESP32
function updateFFTData() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      try {
        var data = JSON.parse(this.responseText);
        drawFFT(data);
      } catch(e) {
        console.log('FFT parse error:', e);
      }
    }
  };
  AJAX.open("GET", "getFFTData", true);
  AJAX.send();
}

// Download FFT data as CSV file
function downloadFFTCSV() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      // Create blob and download
      var blob = new Blob([this.responseText], {type: 'text/csv'});
      var url = window.URL.createObjectURL(blob);
      var a = document.createElement('a');
      var timestamp = new Date().toISOString().replace(/[:.]/g, '-');
      a.href = url;
      a.download = 'fft_data_' + timestamp + '.csv';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  AJAX.open("GET", "getFFTCSV", true);
  AJAX.send();
}

// Toggle between Signal Generator view and FFT-only view
var isFFTOnlyView = false;
function toggleView() {
  isFFTOnlyView = !isFFTOnlyView;
  var btn = document.getElementById('viewToggle');
  var controller = document.getElementById('controllerDiv');
  var infoDIV = document.getElementById('InfoDIV');
  var credit = document.getElementById('credit');
  var power = document.getElementById('power');
  var fftContainer = document.getElementById('fftCanvasContainer');
  var fftTitle = document.getElementById('fftTitle');
  var canvas = document.getElementById('fftCanvas');
  
  if (isFFTOnlyView) {
    // FFT-only view: hide signal generator, show FFT fullscreen
    controller.classList.add('hidden');
    infoDIV.classList.add('hidden');
    credit.classList.add('hidden');
    power.classList.add('hidden');
    fftContainer.style.display = 'block';  // Show FFT container
    btn.innerHTML = 'Show Signal Generator';
    
    // Make FFT canvas fullscreen
    fftContainer.style.position = 'fixed';
    fftContainer.style.top = '70px';
    fftContainer.style.left = '10px';
    fftContainer.style.right = '10px';
    fftContainer.style.bottom = '10px';
    fftContainer.style.margin = '0';
    fftContainer.style.padding = '0';
    fftContainer.style.backgroundColor = '#fff';
    fftContainer.style.zIndex = '150';
    
    fftTitle.style.fontSize = '2em';
    fftTitle.style.marginTop = '0.5em';
    
    canvas.width = window.innerWidth - 80;
    canvas.height = window.innerHeight - 180;
    
    // Redraw with new size
    setTimeout(updateFFTData, 100);
  } else {
    // Normal view: show signal generator, hide FFT
    controller.classList.remove('hidden');
    infoDIV.classList.remove('hidden');
    credit.classList.remove('hidden');
    power.classList.remove('hidden');
    fftContainer.style.display = 'none';  // Hide FFT container
    btn.innerHTML = 'Show FFT Only';
    
    // Reset FFT canvas to normal
    fftContainer.style.position = 'relative';
    fftContainer.style.top = 'auto';
    fftContainer.style.left = 'auto';
    fftContainer.style.right = 'auto';
    fftContainer.style.bottom = 'auto';
    fftContainer.style.margin = '1em 0';
    fftContainer.style.padding = '0';
    fftContainer.style.backgroundColor = 'transparent';
    fftContainer.style.zIndex = 'auto';
    
    fftTitle.style.fontSize = '1.5em';
    fftTitle.style.marginTop = '0';
    
    canvas.width = 1200;
    canvas.height = 300;
  }
}

// you could call the functions directly right here, but I like this better..
window.onload = (event) => {
  goneConsole = true;
  getStatus();
  document.querySelector("#webConsole").focus();
  drawWaveform();
  updateWaveformData();
  // Update waveform every 2 seconds
  setInterval(updateWaveformData, 2000);
  
  // Initialize and update FFT display
  updateFFTData();
  setInterval(updateFFTData, 500);  // Update FFT more frequently (500ms)
  
  // Add hover tooltip for canvas
  var canvas = document.getElementById('waveCanvas');
  var tooltip = document.getElementById('waveTooltip');
  
  canvas.addEventListener('mousemove', function(e) {
    var rect = canvas.getBoundingClientRect();
    var x = e.clientX - rect.left;
    var y = e.clientY - rect.top;
    
    // Build tooltip content
    var modeNames = {'s': 'Sine Wave', 'r': 'Square Wave', 't': 'Triangle Wave', 'w': 'Sawtooth Wave'};
    var tooltipHTML = '<strong>' + modeNames[currentWaveMode] + '</strong><br>';
    tooltipHTML += 'Frequency: ' + formatFrequency(currentFrequency) + '<br>';
    
    if (currentWaveMode !== 's') {
      tooltipHTML += 'Pulse Width: ' + currentPulse + '%<br>';
    }
    
    if (currentWaveMode !== 'r') {
      tooltipHTML += 'Amplitude: ' + currentAmplitude.toFixed(2) + 'V<br>';
      tooltipHTML += 'Peak-to-Peak: ' + (currentAmplitude * 2).toFixed(2) + 'V';
    } else {
      tooltipHTML += 'Amplitude: 3.3V (Full)<br>';
      tooltipHTML += 'Peak-to-Peak: 3.3V';
    }
    
    tooltip.innerHTML = tooltipHTML;
    tooltip.style.display = 'block';
    tooltip.style.left = (e.clientX - rect.left + 15) + 'px';
    tooltip.style.top = (e.clientY - rect.top + 15) + 'px';
  });
  
  canvas.addEventListener('mouseout', function() {
    tooltip.style.display = 'none';
  });
};

// If you add buttons, increase this number to match
var buttonMax = 9;


/*
   Web Console
               */

// Click the title to activate the Web Console..
var WebConsolePage = "<form onsubmit=\"return false;\"><div><input id=\"webConsole\" class=\"nice-input\" onfocus=\"if (this.value=='Command') this.value = ''\" onblur=\"if (this.value=='') this.value = 'Command'\" type=\"text\" value=\"Command\" title=\"Enter commands just as you would in a serial console.\nWhen a response has been received, this input will reset.\"><button onclick=\"sendCommand()\" id=\"send-button\" type=\"submit\" title=\"Click here to send the command. (or hit &lt;enter&gt; from the input)\">Send</button></div></form>";

function createWebConsole() {
  if (goneConsole == false) {
    headerTXT = "" + document.querySelector("#head").value;
    document.querySelector("#head").innerHTML = WebConsolePage;
    goneConsole = true;
    window.setTimeout( function() {
      document.querySelector("#webConsole").focus();
    }, updateDelay);
  }
}

// Send the command..
function sendCommand() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      if (this.responseText != "") {
        postMSG(this.responseText);
      }
      document.querySelector("#webConsole").focus();
      document.querySelector("#webConsole").value = "";
      window.setTimeout( function() {
        getCommandStatus();
      }, updateDelay);
    }
  };
  var myCommand = document.querySelector("#webConsole").value;
  myCommand = myCommand.replaceAll('%', '%25');
  if (myCommand == "") { myCommand = "!"; }
  console.log("Sending Command: " + myCommand);
  AJAX.open("GET", myCommand, true);
  AJAX.send();
}


// Get the command status..
function getCommandStatus() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      if (this.responseText) {
        /* Rather than force the user to reload the page for updated button titles, we can check for
           rename commands and switch the button title right here in JavaScript, using browser CPU cycles.

           This only works if namePreset() outputs *exactly* THIS text: " ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ " */

        if (this.responseText.indexOf("Set name of preset") != -1 ) { // Set name of preset [x] to "Name"
          var regex = /preset \[(.+)\] to \"([^"]+)\"/
          var tData = this.responseText.match(regex);
          if ( parseInt(tData[1]) <= buttonMax ) { // only apply to buttons 1-buttonMax (no need to check for <1)
            document.getElementById("preset_" + tData[1]).title = tData[2]; // Yeah, JavaScript is alright.
          }
        }
        // Similarly, we can clear the titles of wiped presets..
        if (this.responseText.indexOf("Clearing") != -1 ) {
          var regex = /Clearing preset\ (.+)/
          var tData = this.responseText.match(regex);
          if ( parseInt(tData[1]) <= buttonMax ) {
            document.getElementById("preset_" + tData[1]).title = "";
          }
        }

        postMSG(this.responseText);
        window.setTimeout( function() {
          delayedStatus();
          }, updateDelay * 2);
      }
    }
  };
  AJAX.open("GET", "LastMessage", true);
  AJAX.send();
}


/*
    Text Inputs
                  */

// Frequency Change..
function setFreqency() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
      document.querySelector("#frequency").focus();
      document.querySelector("#frequency").value = "";
    }
  };
  var f = "frequency="+document.querySelector("#frequency").value;
  console.log("Sending frequency: " + f);
  AJAX.open("GET", "setFreqency?"+f, true);
  AJAX.send();
}

// Frequency Touch Step Change..
function setStep() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      document.querySelector("#step").focus();
      document.querySelector("#step").value = "";
    }
  };
  var f = "step="+document.querySelector("#step").value;
  console.log("sending step size: " + f);
  AJAX.open("GET", "setStep?"+f, true);
  AJAX.send();
}

// Resolution Bit Depth Change..
function setBitDepth() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      document.querySelector("#bits").focus();
      document.querySelector("#bits").value = "";
    }
  };
  var f = "bits="+document.querySelector("#bits").value;
  console.log("sending bit depth: " + f);
  AJAX.open("GET", "setBitDepth?"+f, true);
  AJAX.send();
}

// Pulse Width Change..
function setPulseWidth() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
      document.querySelector("#pulse").focus();
      document.querySelector("#pulse").value = "";
    }
  };
  var f = "pulse="+document.querySelector("#pulse").value;
  console.log("sending pulse width: " + f);
  AJAX.open("GET", "setPulseWidth?"+f, true);
  AJAX.send();
}

// Amplitude Change..
function setAmplitude() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
      document.querySelector("#amplitude").focus();
      document.querySelector("#amplitude").value = "";
    }
  };
  var f = "amplitude="+document.querySelector("#amplitude").value;
  console.log("sending amplitude: " + f);
  AJAX.open("GET", "setAmplitude?"+f, true);
  AJAX.send();
}



// UP Button..
function setUP() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setUP", true); // use "pulseUP" for pulse width UP, use "resUP" for resolution bits UP
  AJAX.send();
}

// Down Button..
function setDOWN() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setDOWN", true); // use "pulseDOWN" for pulse width DOWN, "resDOWN" for resolution bits DOWN
  AJAX.send();
}


// Set Waveforms..
//
function setSquare() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setSquare", true);
  AJAX.send();
}

function setSine() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setSine", true);
  AJAX.send();
}

function setTriangle() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setTriangle", true);
  AJAX.send();
}

function setSaw() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      postMSG(this.responseText);
      delayedStatus();
      updateWaveformData();
    }
  };
  AJAX.open("GET", "setSaw", true);
  AJAX.send();
}


// Info (?) button..
function getStatus() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      var foo = this.responseText
      foo = foo.replaceAll("\t", "<div>");  // Aaargh! An old pirate trick!
      foo = foo.replaceAll("\n", "</div>"); // Re-usable status data (console+AJAX+direct web access)
      postMSG(foo);
      getFrequency();
      getWaveForm();
    }
  };
  AJAX.open("GET", "status", true);
  AJAX.send();
}

// Get current values from server..
function getFrequency() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      document.getElementById("FreqValue").innerHTML = this.responseText;
    }
  };
  AJAX.open("GET", "frequency", true);
  AJAX.send();
}
function getWaveForm() {
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      document.getElementById("WaveForm").innerHTML = this.responseText;
    }
  };
  AJAX.open("GET", "wave", true);
  AJAX.send();
}


// Reboot your ESP32 device.. (slightly smarter version)
function rebootDevice() {
  postMSG("Rebooting..<br>(auto-reload in 3s)");
  var AJAX = new XMLHttpRequest();
  AJAX.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      window.setTimeout( function() {
        window.location.reload();
      }, 3000);
    }
  };
  AJAX.open("GET", "reboot", true);
  AJAX.send();
}


function delayedStatus() {
    window.setTimeout( function() {
    getStatus();
  }, updateDelay);
}


// Post information to the Info DIV..
function postMSG(message) {
  document.getElementById("InfoDIV").innerHTML = message;
}

</script>
</body>
</html>
)HTML5";

