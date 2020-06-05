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

	let disposable = vscode.commands.registerCommand('memory-management.remoteMemory', function () {
		
		vscode.window.showInformationMessage('The remote memory has been actived!');
		changeRemoteMemoryStatus();

	});

	context.subscriptions.push(disposable);

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
			console.log("el valor de remoteMemoryValue es: " + remoteMemoryValue);
			readJSON();
			panel.webview.html = getWebviewContent();

		  };
	
		  updateWebview();
		  setInterval(updateWebview,500);
			
		})
	  );

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

	console.log("el valor de data es: " + data);

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
  
		  <h2>Memory management table</h2>

		  <label id="lbl1" for="Name">Memoria en uso: local</label>

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

		  if(${remoteMemoryValue}=="1"){
			document.getElementById("lbl1").innerHTML= 'Memoria en uso: remota';
		  }
		  if(${remoteMemoryValue}=="0"){
			document.getElementById("lbl1").innerHTML= 'Memoria en uso: local';
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
