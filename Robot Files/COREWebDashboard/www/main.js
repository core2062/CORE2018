var view = "driver-dashboard";

tabButtons = {};

function initialize() {

    fieldCanvas = document.getElementById('windowCanvas');
    fieldContext = fieldCanvas.getContext('2d');

    windowDiv = document.getElementById('windowDiv');
    windowDiv.addEventListener('dragover', handleDragOver, false);
    windowDiv.addEventListener('drop', handleFileSelect, false);

    creatorToolbar = document.getElementById('toolBar');
    windowWidth = window.innerWidth;
    windowHeight = window.innerHeight;
    autonCreatorInit();
    tabButtons.driverDashboard = document.getElementById("driver-dashboard-button");
    tabButtons.debugDashboard = document.getElementById("debug-dashboard-button");
    tabButtons.autonConfig = document.getElementById("auton-config-button");
    tabButtons.autonCreator = document.getElementById("auton-creator-button");
    view = "auton-creator";
    loop();
}

function loop() {
    updateInput();
    var onColor = '#006a8f';
    var offColor = '#008CBA';
    tabButtons.driverDashboard.style.background = (view === "driver-dashboard")?onColor:offColor;
    tabButtons.debugDashboard.style.background = (view === "debug-dashboard")?onColor:offColor;
    tabButtons.autonConfig.style.background = (view === "auton-config")?onColor:offColor;
    tabButtons.autonCreator.style.background = (view === "auton-creator")?onColor:offColor;
    tabButtons.autonCreator.style.background = (view === "auton-creator")?onColor:offColor;

    windowWidth = window.innerWidth;
    windowHeight = window.innerHeight;

    fieldContext.clearRect(0, 0, windowWidth, windowHeight);
    fieldContext.rect(0, 0, windowWidth, windowHeight);

    if(view === "auton-creator") {
        autonCreatorDataLoop();
        autonCreatorDrawLoop();
    }
    requestAnimationFrame(loop);
}

function handleFileSelect(evt) {
    evt.stopPropagation();
    evt.preventDefault();

    var file = evt.dataTransfer.files[0];
    var read = new FileReader();
    read.readAsText(file);

    read.onloadend = function(){
        console.log(read.result);
		loadPath(read.result);
    }
}

function handleDragOver(evt) {
    evt.stopPropagation();
    evt.preventDefault();
    evt.dataTransfer.dropEffect = 'copy'; // Explicitly show this is a copy.
}