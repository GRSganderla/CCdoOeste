<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Menu Do Cliente</title>
</head>
<body>

 	<h1> Menu</h1>
 	<form action="ClienteController" method= "post">
 		<h3><input type="hidden" name="ID" value="<%out.print(request.getAttribute("clienteId"));%>"/></h3>
  		<h3><input type="submit" value="Consultar/Alterar"></h3>
	</form>
	<h3><input type="submit" value="Solicitar Compra"/></h3>
	<h3><input type="submit" value="Revisar Compra"/></h3>
	<h3><input type="submit" value="Garantia de um Produto"/></h3>
	<h3><input type="submit" value="Acompanhar Entrega"/></h3>
	
	<form action="index.jsp">
	<h3><input type="submit" value="Sair"/></h3>
	</form>
</body>
</html>