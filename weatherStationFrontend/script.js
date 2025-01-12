function showDateTime(){
    let date = new Date();
    date = String(date).slice(0, 24).toLowerCase();

    document.getElementById("dateTime").textContent = date;
}

//update every second
setInterval(showDateTime, 1000);
showDateTime();
