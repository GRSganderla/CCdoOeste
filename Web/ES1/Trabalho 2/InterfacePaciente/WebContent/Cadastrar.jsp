<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Cadastro Paciente</title>
<style>
	label,textarea, input[type = submit]{
		display: block;
	}
	input[type = submit]{
		margin-left: 400px;
		background: #C5F944;
		color:#000000;
		cursor:pointer;
		padding: 3px;
	}
	textarea{
		width: 300px;
		height: 80px;
	}
	html{
		background-color: lightblue;
	}
	body{
		font-family: Arial,sans-serif;
	}
	header h1 {
		text-align: center;
	}
	section h2{
		padding: 10px 0px 10px 150px;
		text-align: left;
		color: #000000;
	}
	.formularios{
		padding: 10px 0px 10px 30px;
		width: 430px;
	    margin: 0px;
	}
	#wrap{
		border:ridge;
		width: 800px;
		margin: auto;
		background: gray;
	}
	#secao{
		width: 560px;
		margin: auto;
		background: #C5C5C5;
	}
	#secaoPrincipal{
		width: 560px;
		margin: auto;
		background: white;
	}
</style>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js"></script>
<script type="text/javascript">

function ajaxcall(){
	
	var cep = document.forms["cadPaciente"]["Cep"].value;;
	
	$.ajax({
		type:"POST",
		url: "/CepController",
		data: {CEP: cep},
		success: function(data){
			
			var result = data;
			$('#Endereco').attr("value", result);
		}
	});
	
	return false;
}
</script>
</head>
<body>
	<div id = "secaoPrincipal">
		<section>
			<div id = "secao">
				<h2> Cadastro de pacientes </h2>
			</div>
			<div class = "formularios">
				<form action="CadastroPaciente" method="post" name="cadPaciente"> 
					<fieldset>
						<legend>Informações cadastrais</legend>
						<label for = "nome">Primeiro Nome:</label>
						<input id = "Nome1" type = "text" name="Nome1"/>
						<label for = "Nome2">Nome do Meio:</label>
						<input id = "Nome2" type = "text" name = "Nome2"/>
						<label for = "Nome3">Ultimo Nome:</label>
						<input id = "Nome3" type = "text" name = "Nome3"/>
						<label for = "CPF">CPF:</label>
						<input id = "CPF" type = "text" name = "CPF"/>
						<label for = "Sexo">Sexo:</label>
						<input id = "Sexo" type = "text" name="Sexo" />
						<label for = "DataNascimento">Data de Nascimento:</label>
						<input id = "Data" type = "text" name="Data"/>
						<label for = "Tipo">Tipo Sanguineo:</label>
						<input id = "Tipo" type = "text" name="Tipo" />
						<label for = "Foto">Foto:</label>
						<input id = "Foto" type = "text" name="Foto"/>
						<label for = "Telefone">Telefone:</label>
						<input id = "Telefone" type = "text" name="Telefone"/>
						<label for = "Telefone2">Telefone 2:</label>
						<input id = "Telefone2" type = "text" name="Telefone2"/>
						<label for = "Email">Email:</label>
						<input id = "Email" type = "text" name="Email" />
						<label for = "Email2">Email 2:</label>
						<input id = "Email2" type = "text" name="Email2" />
						<label for = "Cep">CEP:</label>
						<input id = "Cep" type = "text" name="Cep" onblur="ajaxcall()"/>
						<label for = "Endereco">Endereco:</label>
						<input id = "Endereco" type = "text" name="Endereco" />
						<label for = "Casa">Número da Casa:</label>
						<input id = "Casa" type = "text" name="Casa" />
						<label for = "Complemento">Complemento:</label>
						<input id = "Complemento" type = "text" name="Complemento" />
						<input type = "submit" value = "Concluir"/>
					</fieldset>
				</form>
			</div>
		</section>
	</div>
</body>
</html>