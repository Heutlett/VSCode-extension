// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');

var ffi = require("ffi-napi");
var ref = require('ref-napi');

var $ = require('jquery');

//var ffi = require('ffi');

// Import math library

/**
 * @param {vscode.ExtensionContext} context
 */

var listaGlobal;

var contador = 0;

let folderPath;


function activate(context) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "memory-management" is now active!');

	//copyFiles();

	//readJSON();
	
	//let folderName = vscode.workspace.name; // get the open folder name
	folderPath = vscode.workspace.rootPath; // get the open folder path


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


			readJSON();

			panel.webview.html = getWebviewContent();

		  };
	
		  // Set initial content
		  updateWebview();
	
		  // And schedule updates to the content every second
		  setInterval(updateWebview, 500);
			

		})
	  );

}

function copyFiles(){

	const fs = require('fs');

	// destination will be created or overwritten by default.
	fs.copyFile('/home/heutlett/VSCode-extension/Extension_js_def/memory-management/libraryFiles/pruebax.txt', '/home/heutlett/VSCode-extension/Extension_js_def/memory-management/libraryFiles/pruebax2.txt', (err) => {
	if (err) throw err;
	console.log('File was copied to destination');
	});

}


function readJSON(){

	var fs = require('fs');

	var data = fs.readFileSync(folderPath+"/pretty.json", "utf8");

	var data1 = JSON.parse(data);

	var lista = [];

	if(data1.listaPunteros != null){

		for (var i=0; i< data1.listaPunteros.length; i++){

			var listaElemento = [];
	
			listaElemento[0] = JSON.stringify(data1.listaPunteros[i].id);
			listaElemento[1] = JSON.stringify(data1.listaPunteros[i].refAddress);
			listaElemento[2] = JSON.stringify(data1.listaPunteros[i].refQuantity);
			listaElemento[3] = JSON.stringify(data1.listaPunteros[i].type);
			listaElemento[4] = JSON.stringify(data1.listaPunteros[i].value);
			listaElemento[5] = JSON.stringify(data1.listaPunteros[i].vsptrAdress);
	
			lista.push(listaElemento);
	
		}

	}

	listaGlobal = lista;
	
}

function generateTable(){

	var texto = `var tb1 = document.getElementById("t01");
	`
	for (var i=0; i< listaGlobal.length; i++){

		texto = texto + 

		`
		var row = tb1.insertRow();
		var cell1 = row.insertCell();
		var cell2 = row.insertCell();
		var cell3 = row.insertCell();
		var cell4 = row.insertCell();
		var cell5 = row.insertCell();
		var cell6 = row.insertCell();
		cell1.innerHTML = ` + listaGlobal[i][0] + `;
		cell2.innerHTML = ` + listaGlobal[i][1] + `;
		cell3.innerHTML = ` + listaGlobal[i][2] + `;
		cell4.innerHTML = ` + listaGlobal[i][3] + `;
		cell5.innerHTML = ` + listaGlobal[i][4] + `;
		cell6.innerHTML = ` + listaGlobal[i][5] + `;
		`
  
	}
	return texto;
}

function getWebviewContent() {
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
  
		  <table id="t01">
		  <tr>
			  <th>ID</th>
			  <th>refAddress</th> 
			  <th>refQuantity</th>
			  <th>Type</th>
			  <th>Value</th>
			  <th>VsptrAdress</th>
		  </tr>
		  </table>
  
		  <script>

		  ` + generateTable()  + `
				  
  
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
