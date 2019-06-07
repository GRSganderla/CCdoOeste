<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Excluir Produto</title>
</head>
<body>
	<h1> Excluir Produto </h1>
	<br>
	<form action="ExcluirProdutoController" method="post">
		<br>	
		<h4> Digite o Nome do produto  <input type="text" id=id name="id" > </h4>
		<br>
		<input type="submit" value="Excluir"/>
	</form>
</body>
</html>