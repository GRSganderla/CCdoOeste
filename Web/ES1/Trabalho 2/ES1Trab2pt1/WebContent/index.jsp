<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
		<h1> Login Do Usuário </h1>
	<br>
	<form action="Menu.jsp" method="post">
	<br>
	<h4> Login  <input type="text" id=Login name="Login" > </h4>
	<br>
	<h4> Senha  <input type="text" id="Senha" name="Senha" > </h4>
	<input type="submit" value="Entrar"/>
	</form>
	
	<form action="Cadastrar.jsp" >
	<br> 
	<h4> Não possui cadastro? </h4> <input type="submit" value="Cadastre-se"/>
	</form>
</body>
</html>