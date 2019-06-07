<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Menu do Admin</title>
</head>
<body>
 	
 	<h1> Menu</h1>
 	<form action="Cadastrar-produto.jsp" >
		<input type="submit" value="Cadastrar Produto"/>
	</form>
	<br>
	<form action="Excluir-produto.jsp" >
		<input type="submit" value="Excluir Produto"/>
	</form>
	<br>
	<form action="Consultar-produto.jsp" >
		<input type="submit" value="Consultar/Alterar Produto"/>
	</form>
	<form action="index.jsp">
		<input type="submit" value="Sair">
	</form>
</body>
</html>