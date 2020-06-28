// LOGIN SCRIPT


function helloWorld() {
    return "Hello Typescript World!";
}

let textToAdd:HTMLHeadingElement = document.getElementById("hello-world") as HTMLHeadingElement;
textToAdd.innerHTML = helloWorld();
