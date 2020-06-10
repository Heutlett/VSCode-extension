const vscode = require('vscode');
/*
var ref = require('ref-napi');

var ffi = require('ffi-napi');

var tool = ffi.Library('/home/heutlett/VSCode-extension/Extension_js_def/memory-management/libTools', {
	'copiarArchivo': [ 
		'int', [ 'string', 'string' ] ]
  });
*/

/**
 * @param {vscode.ExtensionContext} context
 */

var listaGlobal = {};
let folderPath;
var remoteMemoryValue;

function activate(context) {

	console.log('Congratulations, your extension "memory-management" is now active!');

	folderPath = vscode.workspace.rootPath; 
	console.log(folderPath);
	clearJSON();

	context.subscriptions.push(
		vscode.commands.registerCommand('memory-management.memoryManagment', () => {
		  
		  const panel = vscode.window.createWebviewPanel(
			'memoryManagment', 
			'Memory managment', 
			vscode.ViewColumn.One, 
			{
				enableScripts: true
			} 
		  );
			
		  const updateWebview = () => {

			getRemoteMemoryValue();
			readJSON();
			panel.webview.html = getWebviewContent();

		  };
	
		  updateWebview();
		  setInterval(updateWebview,500);


		  // Handle messages from the webview
		  panel.webview.onDidReceiveMessage(
			message => {


			  switch (message.command) {

				case 'remoteMemory':
					changeRemoteMemoryStatus();
					
					vscode.window.showInformationMessage("The memory used has been changed to: " + getMemoryInUse() + " memory");
					
					createLoginJSON(message.text);

					return;

				case 'localMemory':
					changeRemoteMemoryStatus();
					
					vscode.window.showInformationMessage("The memory used has been changed to: " + getMemoryInUse() + " memory");
					
					return;
			  }


			},
			undefined,
			context.subscriptions
		  );
			
		})

	  );

}

function createLoginJSON(text){

	var data = text.split(" ");

	const fs = require('fs');
     
	let objectToSave = {
						ip:data[0],
						password:data[1],
						port:data[2],
						user:data[3]
					   }
	 
	console.log(objectToSave);

    fs.writeFile(folderPath + '/conexion.json', JSON.stringify(objectToSave),'utf8', (err) => {
      if (err) throw err;
      console.log('The file has been saved!');
    });

}


function getWebviewContent() {
	return `<!DOCTYPE html>
  <html lang="en">
	  <head>
		  <meta charset="UTF-8">
		  <meta name="viewport" content="width=device-width, initial-scale=1.0">
		  <title>Memory management</title>
  
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

	  	
		  <h1>Memory management table</h1>

		  <h2>Memoria en uso: ` + getMemoryInUse() +  ` </h2>

		  <h2>Data to log in to remote memory</h2>

			<form action="/action_page.php">

			<label id="lblIP" for="fname">IP:</label>
			<input id="inIP" type="text" name="fname"><br><br>

			<label id="lblPass" for="lname">Password:</label>
			<input id="inPass" type="text" name="lname"><br><br>

			<label id="lblPort" for="lname">Port:    </label>
			<input id="inPort" type="text" name="lname"><br><br>

			<label id="lblUser" for="lname">User:    </label>
			<input id="inUser" type="text" name="lname"><br><br>

			<button id="btnRemote" type="button" onclick=changeMemoryRemote()>Connect to remote memory</button>
			<button id="btnLocal" type="button" onclick=changeMemoryLocal()>Change to local memory</button>
			  
			<br><br>

			</form>

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

		  	function changeMemoryLocal(){

				const vscode = acquireVsCodeApi();

				var texto = "";

				vscode.postMessage({
					command: 'localMemory',
					text: texto
				})
				

			  }


			function changeMemoryRemote(){

				const vscode = acquireVsCodeApi();

				var texto = "";

				texto += document.getElementById("inIP").value + " ";
				texto += document.getElementById("inPass").value + " ";
				texto += document.getElementById("inPort").value + " ";
				texto += document.getElementById("inUser").value;

				vscode.postMessage({
					command: 'remoteMemory',
					text: texto
				})

			}

		  ` + generateTable() + `
				  
  
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


function writeLogInInfo(){



	

}

function clearJSON(){

	var fs = require('fs');

	fs.writeFile(folderPath+"/pretty.json", "", function(err) {
	  if (err) {
		return console.log(err);
	  }
	  console.log("El archivo fue creado correctamente");
	});

}

function copyFiles(){

	const fs = require('fs');

	fs.copyFile('/home/heutlett/VSCode-extension/Extension_js_def/memory-management/libraryFiles/pruebax.txt', '/home/heutlett/VSCode-extension/Extension_js_def/memory-management/libraryFiles/pruebax2.txt', (err) => {
	if (err) throw err;
	console.log('File was copied to destination');
	});

}

function readJSONAux(){

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


function readJSON(){

	var fs = require('fs');

	fs.readFile(folderPath+"/pretty.json", 'utf8', function(err, data) {
		if (err) {
			return console.log(err);
		}
		if(data==""){
			return 
		}
		readJSONAux();
	});
	
}

function getRemoteMemoryValue(){

	var fs = require('fs');

	fs.readFile(folderPath+"/remote_memory_conf.txt", 'utf8', function(err, data) {
	if (err) {
		return "0";
	}

	remoteMemoryValue = data;
	
	});

}

function changeRemoteMemoryStatus(){

	var fs = require('fs');

	fs.readFile(folderPath+"/remote_memory_conf.txt", 'utf8', function(err, data) {
	if (err) {
		return "0";
	}

	console.log("el valor de data es: " + data);

	if(data == '1'){

		fs.writeFile(folderPath+"/remote_memory_conf.txt", "0", function(err) {
			if (err) {
			  return console.log(err);
			}
		  });

	}else{

		fs.writeFile(folderPath+"/remote_memory_conf.txt", "1", function(err) {
			if (err) {
			  return console.log(err);
			}
		  });
	}

	});
	return ""
}

function disableRemoteInputs(){

	return `

	document.getElementById("lblIP").hidden = true;
	document.getElementById("lblPass").hidden = true;
	document.getElementById("lblPort").hidden = true;
	document.getElementById("lblUser").hidden = true;
	document.getElementById("inIP").hidden = true;
	document.getElementById("inPass").hidden = true;
	document.getElementById("inPort").hidden = true;
	document.getElementById("inUser").hidden = true;
	document.getElementById("btnRemote").hidden = true;
	document.getElementById("btnLocal").hidden = false;

	`

}

function enableRemoteInputs(){

	return `

	document.getElementById("btnRemote").hidden = false;
	document.getElementById("btnLocal").hidden = true;

	`

}

function generateTable(){


	if(remoteMemoryValue == 1){
		var texto = `var tb1 = document.getElementById("t01"); ` + disableRemoteInputs();
	}else{
		var texto = `var tb1 = document.getElementById("t01"); ` + enableRemoteInputs();
	}
	

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

function getMemoryInUse(){

	if(remoteMemoryValue=="1"){
		return ' remota';
	}
	if(remoteMemoryValue=="0"){
		return ' local';
	}

}
