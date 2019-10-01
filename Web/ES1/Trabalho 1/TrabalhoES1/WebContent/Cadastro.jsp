<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Cadastro</title>
</head>
<body>

	<h1> Tela de Cadastro </h1>
	<br>
	<form action="CadastroClienteController" method="post">
		<br>
		
		<h4> Nome Completo  <input type="text" id=Nome name="Nome" ></h4>
		
		<h4> Email  <input type="text" id=Email name="Email" ></h4>
		
		<h4> CPF  <input type="text" id=CPF name="CPF" > CNPJ <input type="text" id= "CNPJ" name = "CNPJ"> </h4>

		<h4> Senha  <input type="password" id=Senha name="Senha" > Confirme a senha  <input type="password" id=Senha1 name="Senha1" ></h4>
		
		<h4> CEP <input type="text" id=CEP name="CEP"> </h4>
		
		<h4> Rua  <input type="text" id=Rua name="Rua" > Número <input type="text" id=num name="Numero"></h4>
		
		<h4> Bairro  <input type="text" id=Bairro name="Bairro" ></h4>
		
		<h4> Complemento <input type="text" id=complemento name="Complemento"></h4>
		
		<h4> Cidade  <input type="text" id=Cidade name="Cidade"> Estado <input type="text" id=Estado name="Estado"> </h4>
		
		<h4> País  <input type="text" id=País name="País" ></h4>
		<br>            
		<br>            
		<input type="submit" value="Cadastrar"/>
	</form>

</body>
</html>