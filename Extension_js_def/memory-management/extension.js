// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below

const vscode = require('vscode');

var ffi = require("ffi-napi");

var ref = require('ref-napi');
//var ffi = require('ffi');

// Import math library

const libVSPtr_DynamicLibrary = ffi.Library("/home/heutlett/VSCode-Memory-Manager/Extension_Tests/lib/libVSPtr_DynamicLibrary", {
    "CountPeople": [
        "int", []
	],
	"recibo": [
		"int", []
	]
});

//console.log(libVSPtr_DynamicLibrary.getInfo(15));

//var buffer = new Buffer(32); // allocate 32 bytes for the output data, an imaginary MD5 hex string.
//mathLibrary.get_md5_string(buffer);
//var actualString = ref.readCString(buffer, 0);

//console.log(actualString);


// this method is called when your extension is activated
// your extension is activated the very first time the command is executed



/**
 * @param {vscode.ExtensionContext} context
 */



function activate(context) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "memory-management" is now active!');

	

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with  registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('memory-management.helloWorld', function () {
		// The code you place here will be executed every time your command is executed

		// Display a message box to the user
		vscode.window.showInformationMessage('Hello World from Memory_management!');
	});

	context.subscriptions.push(disposable);

	context.subscriptions.push(
		vscode.commands.registerCommand('memory-management.memoryManagment', () => {
		  // Create and show a new webview
		  const panel = vscode.window.createWebviewPanel(
			'memoryManagment', // Identifies the type of the webview. Used internally
			'Memory managment', // Title of the panel displayed to the user
			vscode.ViewColumn.One, // Editor column to show the new webview panel in.
			{

				enableScripts: true

			} // Webview options. More on these later.
		  );


		  const updateWebview = () => {
			//const cat = iteration++ % 2 ? 'Compiling Cat' : 'Coding Cat';
			//panel.title = cat;
			var number = Math.random();
			panel.webview.html = getWebviewContent(libVSPtr_DynamicLibrary.recibo());
		  };
	
		  // Set initial content
		  updateWebview();
	
		  // And schedule updates to the content every second
		  setInterval(updateWebview, 100);

			
			

			

		})
	  );

}

function foo(){

	console.log('hola');

}


function getWebviewContent(number) {
	return `<!DOCTYPE html>
  <html lang="en">
	  <head>
		  <meta charset="UTF-8">
		  <meta name="viewport" content="width=device-width, initial-scale=1.0">
		  <title>Memory managment</title>
  
		  <style>
		  table, th, td {
			  border: 1px solid black;
			  text-align: left;
		  }
		  table#t01 {
			  width: 100%;    
			  background-color: #ffffff;
			  color: black;
		  }
		  </style>
	  </head>
  
	  <body>
  
		  <h2>Memory managment table</h2>
  
		  <input type="button" value=${number} onclick="myFunction2();"/>
  
		  <table id="t01">
		  <tr>
			  <th>Data type</th>
			  <th>Data value</th> 
			  <th>Memory location</th>
			  <th># references in GC</th>
		  </tr>
		  </table>
  
		  <script>

		  	  function myFunction2(){

					

				}
  
			  function myFunction(){ 
  
				  var tb1 = document.getElementById("t01");
				  var row = tb1.insertRow();
				  var cell1 = row.insertCell();
				  var cell2 = row.insertCell();
				  var cell3 = row.insertCell();
				  var cell4 = row.insertCell();
				  cell1.innerHTML = "123";
				  cell2.innerHTML = "123";
				  cell3.innerHTML = "123";	
				  cell4.innerHTML = "123";
			  
			  }
  
		  </script>
  
	  </body>
  
  </html>`;
}

exports.activate = activate;

// this method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}
