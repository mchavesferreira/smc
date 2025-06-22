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

.card2{
    max-width: 150px;
    min-height: 100px;
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

.oled {
    width: 128px;
    height: 64px;
    background-color: black;
    color: #00FF00;
    font-family: 'Courier New', monospace;
    font-size: 12px;
    padding: 5px;
    border: 2px solid #00FF00;
    border-radius: 4px;
    overflow: hidden;
    white-space: pre-line;
    line-height: 1.2;
  }

</style>
<body>

<div class="card">
    <h3>Exemplo Máquina de Café</h4>
    <div class="menu-item">
        <span>Café:</span>
        <select id="cafe">
            <option value="s">Sim</option>
            <option value="n">Não</option>
        </select>
    </div>
    <div class="menu-item">
        <span>Tamanho:</span>
        <select id="tamanho">
            <option value="p">300ml</option>
            <option value="m">500ml</option>
            <option value="g">700ml</option>
        </select>
    </div>
    <div class="menu-item">
        <span>Leite:</span>
        <select id="leite">
            <option value="s">Sim</option>
            <option value="n">Não</option>
        </select>
    </div>
        <div class="menu-item">
        <span>Cha:</span>
        <select id="cha">
            <option value="s">Sim</option>
            <option value="n">Não</option>
        </select>
    </div>
    <button onclick="fazerPedido()">Fazer Pedido</button>
    <button onclick="cancelarPedido()">Cancelar Pedido</button>
    <h1>Status:<span id="textoserial"></span></h1>

<div class="card2">
  <div class="oled" id="oled">
    ...
  </div>
</div>


</div>
<script>
function fazerPedido() {
    var cafev = document.getElementById("cafe").value;
    var tamanhov = document.getElementById("tamanho").value;
    var chav = document.getElementById("cha").value;
      var leitev = document.getElementById("leite").value;

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            var resposta = this.responseText;
            var pedidoRealizado = "Pedido realizado!";
           // var descricaoPedido = "Descrição do pedido: Cafe de " + cafe + ", copo de " + tamanho + ", cha " + cha+ ", leite " + leite;

            document.getElementById("textoserial").innerHTML = pedidoRealizado + "<br>" ;
            
        }
    };
    xhttp.open("GET", "/fazerpedido?pedido&cafe=" + cafev + "&tamanho=" + tamanhov + "&cha=" + chav + "&leite=" + leitev, true);
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

function  getgtexto() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    // verifica se url esta disponivel (cod. 200), bustitui o valor lido  no ID  textoserial do html
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("oled").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "/msgoled", true);  // busca a url readADC por meio do metodo GET
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


setInterval(function() {
  getgtexto();  // busca a url e substitui no ElementById
}, 5000); //5000mSeconds taxa de atualização

</script>





</body>
</html>
)=====";
