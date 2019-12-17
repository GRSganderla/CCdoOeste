<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Chat</title>

<link rel="stylesheet" type="text/css" href="./css/foundation.css" />
<script>
	function alerta(){
		alert("Só um instante enquanto a pagina com o resultado da consulta é gerado...");
	}
</script>
</head>
<body>

	<div class="title-bar" data-responsive-toggle="responsive-menu"
		data-hide-for="medium">
		<button class="menu-icon" type="button" data-toggle="responsive-menu"></button>
		<div class="title-bar-title">Menu</div>
	</div>

	<div class="top-bar" id="responsive-menu">
		<div class="top-bar-right">
			<ul class="dropdown menu" data-dropdown-menu>
				<li><a class="button" href="index.jsp"
					style="margin-right: 5px;">Nota de Venda</a></li>
				<li><a class="button" href="produto.jsp"
					style="margin-right: 5px;">Produto</a></li>
				<li><a class="button" href="" style="margin-right: 5px;">Chat</a></li>
				<li><a class="button" href="consultaNota.jsp">Consulta</a></li>
			</ul>
		</div>
	</div>

	<form action="chat" method="post">
		<h1 class="text-center">Chat</h1>

		<div class="grid-container">
			
			<div class="grid-x grid-padding-x">

				<h3>Olá, Sou a IA de Consulta do Controle de Estoque, o que deseja?</h3>

			</div>

			<div class="row">
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Mensagem:</span> <input
							id="msg" class="input-group-field" type="text"
							name="msg" step="0.01">
					</div>
				</div>
			</div>
			
			<input type="submit" class="button float-right" value="Enviar" onclick="alerta()"></input>
		</div>
	</form>

	<!-- 	<div class="grid-container text-center"> -->
	<!-- 		<div class="grid-x grid-margin-x grid-margin-y grid-padding-y"> -->

	<!-- 			<ul></ul> -->

	<!-- 			<div class="medium-12 cell"> -->
	<!-- 				<div class="input-group"> -->
	<!-- 					<input id="cod" class="input-group-field" type="text" placeholder="Digite a sua mensaem"></input> -->
	<!-- 					<div class="input-group-button"> -->
	<!-- 						<button class="button" type="button" onclick="insertChat()" -->
	<!-- 							id="botao_chat">+</button> -->
	<!-- 					</div> -->
	<!-- 				</div> -->
	<!-- 			</div> -->

	<!-- 		</div> -->
	<!-- 	</div> -->

	<script
		src=https://assistant-web.watsonplatform.net/loadWatsonAssistantChat.js></script>
	<script>
		window.loadWatsonAssistantChat({
			integrationID : "719cf991-9125-4c65-93ba-f478247f1c42", // The ID of this integration.
			region : "us-east" // The region your integration is hosted in.
		}).then(function(instance) {
			instance.render();
		});
	</script>

	<script src="./js/vendor/jquery.js" type="text/javascript"></script>
	<script src="./js/vendor/foundation.js" type="text/javascript"></script>
	<script src="./js/app.js" type="text/javascript"></script>
	<script src="./js/auxiliar.js" type="text/javascript"></script>

</body>
</html>