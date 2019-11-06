<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
      <style>
      	  b { 
		  font-weight: bold;
		  }
     	  input[type=submit] {
		  background-color: #4CAF50;
		  border: none;
		  color: white;
		  padding: 16px 32px;
		  text-decoration: none;
		  margin: 4px 2px;
		  cursor: pointer;
		  position: relative;
          display: block;
          margin : 0 auto;
		  border-radius: 8px;
		 }		
      	 input[type=text] {
		  width: 80%;
		  padding: 12px 20px;
		  margin: 8px 0;
		  box-sizing: border-box;
		  border-radius: 4px;
		 }
      	 fieldset {
      	 	background-color: #e6e6e6;
      	 	 display: block;
  			margin-left: 2px;
  			margin-right: 2px;
  			padding-top: 0.35em;
  			padding-bottom: 0.625em;
  			padding-left: 0.75em;
 			padding-right: 0.75em;
  			border: 2px groove (internal value);
      	 }
      	 body {
      	 	background-color: #80d4ff;
      	 }
         .site div{
         width: 700px;
         height: 700px;
         position: absolute;
         left: 50%;
         top: 50%;
         transform: translate(-50%, -50%);
         }
         .header div{
         width:100px;
         height:100px;
         }
         .conteudo div{
         width:1100px;
         height:500px;
         } 
         .footer div{
         width:1000px;
         height:100px;
         }
         .conteudo-left div{
         width:600px;
         height:100px;
         float:left;
         }
         .conteudo-right{
         width:500px;
         height:100px;
         float:left;
         }
         .conteudo-left-left{
         width: 300px;
         height: 100px;
         float:left;
         }
         .conteudo-right-right{
         width: 300px;
         height: 100px;
         float:left;
         }
         table {
		  width:100%;
		}
		table, th, td {
		  border: 1px solid black;
		  border-collapse: collapse;
		}
		th, td {
		  padding: 15px;
		  text-align: center;
		}
		h4{
		  text-align: center;
		}
      </style>
<title>Endereço Especifico Resultado pela Consulta do Site</title>
</head>
<body>

	<div class="site">
         <div class="header"></div>
         <div class="conteudo">
         <fieldset>
         <h3> Endereço Especifico pego do Site: <br></h3><h4>${Site}</h4>
         	<table style="width:100%">
         	<tr>
         		<th> Nro </th>
         		<th> Complemento </th>
         		<th> CEP </th>
         		<th> Lougradouro </th>
         		<th> Bairro </th>
         		<th> Cidade </th>
         		<th> Unidade da Federação </th>
         		<th> Pais </th>
         	</tr>
         	<tr>
         		<td>${Endereco[2]}</td>
				<td>${Endereco[3]}</td>
				<td>${Endereco[0]}</td>
				<td>${Endereco[1]}</td>
				<td>${Endereco[4]}</td>
				<td>${Endereco[5]}</td>
				<td>${Endereco[6]}</td>
				<td>${Endereco[7]}</td>
         	</tr>
         	</table>
         	<br>
			<form action="index.jsp">
				<input type="submit" value="Voltar"/>
			</form>
			</fieldset>
         </div>
      </div>
</body>
</html>