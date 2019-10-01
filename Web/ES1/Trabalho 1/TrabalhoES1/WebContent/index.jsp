<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Login</title>
</head>
<body>
	
	<h1> Login Do Usuário </h1>
	<br>
	<form action="LoginController" method = "post">
	<h3> Login  <input type="text" id="Login" name="Login" > </h3>
	<h3> Senha  <input type="password" id="Senha" name="Senha" > </h3>
	<input type="submit" value="Entrar"/>
	</form>
	<br> 
	<h3> Não possui cadastro? <a href="Cadastro.jsp" > Cadastre-se</a></h3>
	
</body>
</html>