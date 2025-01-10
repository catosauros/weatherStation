function showDateTime(){
    let date = new Date();
    date = String(date).slice(0, 24).toLowerCase();

    document.getElementById("dateTime").textContent = date;
}

function showTemp(){
    document.getElementById("tempReport").style.display = "block";
    document.getElementById("shadow").style.display = "block";
}

function hideTemp(){
    document.getElementById("tempReport").style.display = "none";
    document.getElementsById("shadow").style.display = "none";
}
//update every second
setInterval(showDateTime, 1000);
showDateTime();
