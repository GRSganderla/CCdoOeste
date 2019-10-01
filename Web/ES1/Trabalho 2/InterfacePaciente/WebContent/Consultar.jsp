<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	
		
	
	<form action="Menu.jsp" method="post">
	
	<h4> Nome Completo : <%out.print(request.getAttribute("Nome1"));%> <%out.print(request.getAttribute("Nome2"));%> <%out.print(request.getAttribute("Nome3"));%> </h4>
	<h4> Sexo : <%out.print(request.getAttribute("Sexo"));%> </h4>
	<h4> Data Nascimento : <%out.print(request.getAttribute("Data"));%> </h4>
	<h4> Tipo Sanguíneo : <%out.print(request.getAttribute("Tipo"));%> </h4>
	<h4> CPF : <%out.print(request.getAttribute("CPF"));%> </h4>
	<h4> Número Casa : <%out.print(request.getAttribute("Casa"));%> Complemento : <%out.print(request.getAttribute("Complemento"));%> </h4>
	<h4> Emails : <%out.print(request.getAttribute("Email"));%> <%out.print(request.getAttribute("Email2"));%> </h4>
	<h4> Telefones : <%out.print(request.getAttribute("Telefone"));%> <%out.print(request.getAttribute("Telefone2"));%></h4>
	
	<h4><input type="submit" value="Voltar"></h4>
	</form>
		
</body>
</html>