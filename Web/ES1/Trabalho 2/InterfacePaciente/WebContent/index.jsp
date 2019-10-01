<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	<h1> Menu</h1>
 	<h3> Bem vindo</h3>
 	<form action="Cadastrar.jsp" method= "post" >
		<input type="submit" value="Cadastrar"/>
	</form>
 	<form action="ConsultarPaciente" method= "post" >
 		<h4> CPF <input type="text" id=CPF name="CPF" > </h4>
		<input type="submit" value="Consultar"/>
	</form>
	
</body>
</html>