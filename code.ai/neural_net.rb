#!/usr/bin/ruby

=begin
A multilayer perceptron implementation for fun, clear understanding and profit.

Author Misgana Bayetta <misgana.bayetta@gmail.com> 2016

=end

class Utility
  # A sigmoid function is  1/(1+e^-x)
  def self.sigmoid x = [], w = []
    1/(1+ Math.exp(-1 * dotp(x,w)))
  end

  def self.dotp x = [], w = []
    sum, i, size = 0, 0, x.size
    while i < size
      sum += x[i] * w[i]
      i += 1
    end
    sum    
  end

end


class Layer
  def initialize nunits, input = [] , learning_rate
    @theta = [] #two dimensional array Theta
    @ouput = [] 
    @sigma = []
    @X = []     # NxM where N is the number of units and M is the input vect size
    @nu = learning_rate
    init_weight( nunits, input.size() )
  end

  def init_weight nunit, ninput
    nunit.times do
      row = []
      ninput.times do
        row.push(0.1) # TODO make it more flexible.
      end
      @theta.push(row)
    end
  end

  def input
    @X
  end

  def output
    @output
  end
  
  def set_input input
    @X = input
  end

  def weights
    @theta
  end

  def set_weight weight
    @theta = weight
  end

  def nunits
    @theta.size()
  end

  # returns a vector of outputs of applying forward propagation at this layer.
  def compute_output
   for unit_weight in @theta
     @output.push(Utility.sigmoid(@X,unit_weight))
   end
   @output
  end

  # Computes error and updates weights accordingly.
  # @param sigma - The error vector from downstream layer mx1  dimension where m is the number of units
  # @param weight - The weight vector from downstream layer 
  # @return - The computed error vector of this layer given the error
  #           vector of the proceding layer.
  def compute_sigma sigma, weight, output_vec
    sigma = []
    for i in 0..@theta.size()-1 do
      s = output_vec[i]*(1-output_vec[i])
      for k in 0..sigma.size()-1 do
        s = s + sigma[k]*weight[k][i]
      end
      sigma.push(s)
    end
    @sigma = sigma

    @sigma
  end
 
  def update_weights
    for i in 0..@sigma.size()-1 do
      for n in 0..@X.size()-1 do
        for m in 0..@X[n].size()-1 do
          delta = @nu * @sigma[i] * @X[n][m]
          @theta[n][m] = @theta[n][m] - delta
        end
      end
    end
  end

end


class NeuralNet
  def initialize input , nlayer, output = []
    @X = input # A two dimensiona input MxN where M is the total rows of training data and N is number of features
    @Y = output # A two dimension output of form MxK where M is total rows of training data and K is the number of outputs. K=1 for binary classifier.
    @hidden_layers  = []
    @lambda = 0
    @output_layer = Layer.new(output[0].size())
    @nlayer = nlayer
  end

  def regularization_value
    total = 0
    for layer in @hidden_layers
      # sum each elements except column 0 which is the bias term.
      layer_sum = 0
      for i in 1..layer.size()-1 do  #for each units of this hidden layer
        for j in 1..layer[0].size()-1 do #for each non bias weights of this unit
          layer_sum = layer_sum + layer[i][j]
        end
      end
      total = total + sum
    end
    (@lambda/2*@X.size())*total
  end

  def cost
    total = 0
    for i in 0..@X.size() do
      sum = 0
      for j in 0..@Y[i].size() do
        hypothesis = Utility.sigmoid(@X[i],@output_layer.weights[j])
        sumtmp = @Y[i][j] * Math.log10(hypothesis) + ((1 - @Y[i][j]) * Math.log10(1-hypothesis))
        sum = sum + sumtmp
      end
      total = total + sum
    end
    ((-1/@X.size()) * total) + regularization_value()
  end

  # Computes the dE/dnet_out vector of the output layer
  # return a vector (T - O)*O*(1-O) in maxtrix form
  def sigma_output input_vect
    weights = @output_layer.weights
    sigma = []
    for i in 0..weights.size()-1
      o = Utility.sigmoid(input_vec, weights[i]) #output computed 
      t = @output_layer.output[i] # target
      sigma.push( ((t-o)*o*(1-o)) )
    end
    sigma
  end

  def update_output_weight sigma, nu
    weights = @output_layer.weights
    for i in 0..weights.size()-1 do
      for i in 0..weights.size()-1 do
        delta = nu * sigma[i] * @output_layer.input[n][m]
          weights[n][m] = weights[n][m] - delta
      end
    end
    @output_layer.set_weight(weights)

  end

  # Main method to start the training. 
  def train
    epoch = 0
    until epoch < 5000 do
      epoch = epoch + 1
      layers = @hidden_layers + @output_layer
      # Forward propagate.
      # i.e compute outputs based on input and current estimated weight vector 
      # starting from hidden layer one to the final output layer.
      for i in  0..layers.size()-2
        outputs = layers[i].compute_output()
        layers[i+1].set_input(outputs)
      end

      # Juz making sure values are updated. No refs in ruby AFAIK.
      @output_layer = layers.pop()
      @hidden_layers = layers

      # Compute hypothesis
      @output_layer.compute_output()

      # Backward propagate.
      # i.e compute error on the output layer and propagate adjustment values back
      # the the hidden units iteratively till the first hidden unit.
      sigma = sigma_output()
      i=@hidden_layers.size()-1
      while i >= 0 do
        sigma = @hidden_layers[i].compute_sigma(sigma,@utput_layer.weights) #TODO add output vec
      end
    end

  end

  #TODO Add/remove hidden layers and units dynamically
end


