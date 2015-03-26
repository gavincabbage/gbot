function simple_command(command, direction)
{
    var url = "/" + command + "/" + direction;
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
