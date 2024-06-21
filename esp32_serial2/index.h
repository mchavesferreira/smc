const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
      <title>ESP32 Web Form</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta charset="UTF-8">
    </head>
<style>
body {
    background-image: url('https://th.bing.com/th/id/OIG.MbP81HSn3hqRMeZV8ZpD?w=270&h=270&c=6&r=0&o=5&dpr=1.3&pid=ImgGn');
    background-size: 70% auto;
    background-repeat: no-repeat;
    background-position: center;
    background-color: black;
}


.card{
    max-width: 400px;
    min-height: 400px;
    background: rgba(2, 184, 117, 0.8);
    padding: 30px;
    box-sizing: border-box;
    color: #FFF;
    margin:20px;
    box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
    text-align: center;
}

.menu-item {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 20px;
}

.menu-item select {
    width: 120px;
    padding: 10px;
    font-size: 16px;
    border-radius: 4px;
    border: none;
}

.menu-item span {
    font-size: 20px;
    font-weight: bold;
}

</style>
<body>

<div class="card">
    <h4>Projeto Máquina de Milkshake</h4>
    <div class="menu-item">
        <span>Sabor:</span>
        <select id="sabor">
            <option value="chocolate">Chocolate</option>
            <option value="morango">Morango</option>
            <option value="acai">Acai</option>
        </select>
    </div>
    <div class="menu-item">
        <span>Tamanho:</span>
        <select id="tamanho">
            <option value="300">300ml</option>
            <option value="500">500ml</option>
            <option value="700">700ml</option>
        </select>
    </div>
    <div class="menu-item">
        <span>Calda:</span>
        <select id="calda">
            <option value="chocolate">Chocolate</option>
            <option value="morango">Morango</option>
        </select>
    </div>
    <button onclick="fazerPedido()">Fazer Pedido</button>
    <button onclick="cancelarPedido()">Cancelar Pedido</button>
    <h1>Status:<span id="textoserial"></span></h1>
</div>
<script>
function fazerPedido() {
    var sabor = document.getElementById("sabor").value;
    var tamanho = document.getElementById("tamanho").value;
    var calda = document.getElementById("calda").value;

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            var resposta = this.responseText;
            var pedidoRealizado = "Pedido realizado com sucesso!";
            var descricaoPedido = "Descrição do pedido: sabor de " + sabor + ", copo de " + tamanho + "ml com calda " + calda;

            document.getElementById("textoserial").innerHTML = pedidoRealizado + "<br>" + "<br>" + descricaoPedido;
            
        }
    };
    xhttp.open("GET", "/fazerpedido?a=1&b=2&c=3&sabor=" + sabor + "&tamanho=" + tamanho + "&calda=" + calda, true);
    xhttp.send();
}

function atualizarStatus() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            var resposta = this.responseText;
            
            // Verifica se a resposta inclui "Fim do processo"
            if (resposta.includes("Fim do processo")) {
                document.getElementById("mensagem").innerHTML = "Pedido finalizado";
            }
        }
    };
    xhttp.open("GET", "/status", true);
    xhttp.send();
}
function cancelarPedido() {
    document.getElementById("textoserial").innerHTML = "Pedido cancelado";

     // Enviar uma requisição para função cancelar pedido
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/cancelarpedido", true);
    xhttp.send();
}

// Função para atualizar o status a cada 5 segundos
setInterval(atualizarStatus, 2000);
</script>





</body>
</html>
)=====";
