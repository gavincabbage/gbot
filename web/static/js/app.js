function simple_command(command, direction)
{
    var url = "http://10.0.0.100:4282/" + command + "/" + direction;
    var xmlHttp = new XMLHttpRequest();

    xmlHttp.onreadystatechange = function()
    {
        if (xmlHttp.readyState==4) {

            console.log(url + " : " + xmlHttp.status);
        }
    }

    xmlHttp.open("GET", url, true);
    xmlHttp.send();
}

function move(direction)
{
    simple_command("move", direction);
}

function look(direction)
{
    simple_command("look", direction);
}

function distance()
{
    //var url = "/" + command + "/" + direction;
    var url = "/distance"
    var xmlHttp = new XMLHttpRequest();

    xmlHttp.onreadystatechange = function()
    {
        if (xmlHttp.readyState==4) {

            console.log(url + " : " + xmlHttp.status + " : " + xmlHttp.responseText);
        }
    }

    xmlHttp.open("GET", url, true);
    xmlHttp.send();
}
