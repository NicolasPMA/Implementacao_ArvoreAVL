# Implementacao_ArvoreAVL
 Este é um código feito para implementar os conceitos estudados de Arvore AVL.

 ## 🚀 Funcionalidade
- Realiza a leitura de um arquivo contendo uma árvore fornecido pelo usuario.
- Imprime a árvore nos formatos: prá-ordem, em-ordem, pós-ordem e em largura.
- Verifica se um elemento existe na árvore.
- Imprime o nível de um nó.
- Imprime as folhas menores que um valor x.
- Insere um nó na árvore.
- Remove um nó da árvore.

  ## 💻 Tecnologia utilizada

  - C: Linguagem de programação principal.

## 📁 Arquivo com uma árvore AVL
- Em primeiro lugar, eu recomendo que o arquivo esteja em .txt (não testei em outros formatos). 
- Em segundo lugar é necessário que a árvore seja uma árvore AVL, o código não realiza uma verificação de qual modelo de árvore está sendo carregada.
- A estrutura da árvore utilizada no arquivo precisa ser nesse formato: (30(20(10(3(-1)(-1))(15(-1)(-1)))(25(-1)(-1)))(40(35(31(-1)(-1))(39(-1)(-1)))(45(-1)(-1))))
- A construção da árvore é feita por padrão em pré-ordem e o -1 equivale ao NULL.

 ## 💡 Como funciona
 Quando o rodar o código, um menu de opções será apresentado.
 1. Ler uma arvore de um arquivo fornecido pelo usuario
 - O usuário deve fornecer um arquivo contendo uma árvore AVL.
 - "arvoreavl.txt"

 3. Imprimir a árvore (opcoes: pré-ordem; em-ordem; pás-ordem; e em largura)
 - O usuário deve escolher o número respectivo ao modo de impressão desejado.
 
 4. Verificar se um elemento x existe na árvore
 - O usuário deve fornecer o valor do elemento para verificação.
 
 5. Imprimir o nível de um no x
 - O usuário deve fornecer o valor correspondente ao nível desejado para impressão.
   
 6. Imprimir as folhas menores que um valor x
 - O usuário deve fornecer um valor e será impresso todas as folhas com valores menores do que o fornecido pelo usuário.
    
 7. Inserir um no x na árvore
 - O usuário deve fornecer um valor para ser inserido na árvore.
    
 8. Remover um no x da árvore
 - O usuário deve fornecer um valor para ser removido da árvore.
    
 9. Sair

## ⚙ Como o código funciona

O código é feito a partir dos conceitos gerais de uma árvore AVL. Primeiramente é necessário que a árvore fornecida pelo usuário seja balanceada e ordenada. 
Desse modo, todos o código irá rodar sem nenhum tipo de problema. Conceitos utilizados:
- Fator de Balanceamento.
- Rotações simples e duplas.
- Modo de impressão (pré-ordem, em-ordem, pós-ordem e largura).
- Recursão.
