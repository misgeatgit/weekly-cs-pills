#!/usr/bin/ruby

=begin
A multilayer perceptron implementation for fun, clear understanding and profit.

Author Misgana Bayetta <misgana.bayetta@gmail.com> 2016

=end

class Utility
  # A sigmoid function is  1/(1+e^-x)
  def self.sigmoid x = [], w = []
    1.0/(1.0 + Math.exp(-1.0 * dotp(x,w)))
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
  attr_accessor :weights, :output, :sigma, :input, :learning_rate
  def initialize nunits,ninput, learning_rate = 0.1 
    @weights = [] #two dimensional array Theta
    @ouput = [] 
    @sigma = []
    @input = []     # NxM where N is the number of units and M is the input vect size
    @learning_rate = learning_rate
    init_weight( nunits, ninput )
  end

  def init_weight nunit, ninput
    nunit.times do
      row = []
      ninput.times do
        row.push(0.01) # TODO make it more flexible.
      end
      @weights.push(row)
    end
  end

  def nunits
    weights.size()
  end

  # returns a vector of outputs of applying forward propagation at this layer.
  def compute_output
    @output = []
    for unit_weight in @weights
      @output.push(Utility.sigmoid(@input,unit_weight))
    end
    @output
  end

  def update_weights
    for i in 0..@weights.size()-1 do
      for j in 0..@weights[0].size()-1 do
        @weights[i][j] = @weights[i][j] + (@learning_rate * @sigma[i] * @input[j])
      end
    end
    @weights
  end


end

class HiddenLayer < Layer
  # Computes error and updates weights accordingly.
  # @param sigma - The error vector from downstream layer mx1  dimension where 
  # m is the number of units
  # @param weight - The weight vector from downstream layer 
  # @return - The computed error vector of this layer given the error
  #           vector of the proceding layer.
  def compute_sigma sigma, weights
    @sigma = []
    for i in 0..@weights.size()-1 
      s = @output[i]*(1-@output[i])
      for k in 0..sigma.size()-1 
        s = s + sigma[k]*weights[k][i]
      end
      @sigma.push(s)
    end
    @sigma
  end

end

class OutputLayer < Layer
  attr_accessor :target
  def compute_sigma
    @sigma = []
    for i in 0..@weights.size()-1
      o = @output[i] 
      t = @target[i] # target
      @sigma.push( ((t-o)*o*(1-o)) )
    end
    @sigma
  end

end


class MultiLayerPerceptron

  def initialize input, hidden_layers, output 
    @X = input # A two dimensiona input MxN where M is the total rows of training
    # data and N is number of features
    @Y = output # A two dimension output of form MxK where M is total rows of 
    # training data and K is the number of outputs. K=1 for binary classifier.
    @hidden_layers  = hidden_layers
    @output_layer = OutputLayer.new(output[0].size(),output[0].size())
    @lambda = 0
  end


  # Main method to start the training. 
  def train max_epoch
    epoch = 0
    while epoch < max_epoch do
      for d in 0..@X.size()-1
        epoch = epoch + 1
        @output_layer.target = @Y[d]
        @hidden_layers[0].input = @X[d]
        
        # Forward propagate.
        # i.e compute outputs based on input and current estimated weight vector 
        # starting from hidden layer one to the final output layer.
        output = @hidden_layers[0].compute_output
        for i in 1..@hidden_layers.size()-1 
            @hidden_layers[i].input = output
            output = @hidden_layers[i].compute_output
        end
        @output_layer.input = output
        @output_layer.compute_output

        # Backward propagate.
        # i.e compute error on the output layer and propagate adjustment values back
        # the the hidden units iteratively till the first hidden unit.
        sigma = @output_layer.compute_sigma
        weights = @output_layer.update_weights
       
        i = @hidden_layers.size()-1
        while i >= 0 do
          sigma = @hidden_layers[i].compute_sigma(sigma,weights)
          weights = @hidden_layers[i].update_weights
          i = i - 1
        end
      end
    end
    dump_weights
  end

  def dump_weights
    puts "Weights starting from Hiddent Layer One\n"
    for layer in @hidden_layers
      for weight in layer.weights
        puts weight.join(' ')
      end
      puts 
    end
    for weight in @output_layer.weights
      puts weight.join(' ')
    end
    puts
  end

  #TODO update these formulae
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
    for i in 0..@X.size()-1
      sum = 0
      for j in 0..@Y[i].size()-1
        hypothesis = Utility.sigmoid(@X[i],@output_layer.weights[j])
        sumtmp = @Y[i][j] * Math.log10(hypothesis) + ((1 - @Y[i][j]) * Math.log10(1-hypothesis))
        sum = sum + sumtmp
      end
      total = total + sum
    end
    ((-1/@X.size()) * total) + regularization_value()
  end

  #TODO Add/remove hidden layers and units dynamically
end

# TESTING
#
hidden_layers = [HiddenLayer.new(4,4,0.1)]
input = [ [0,0,0,1],
          [0,0,1,1],
          [0,1,1,1],
          [1,1,1,1],
          [0,0,1,0],
          [0,1,1,0],
          [1,1,1,0],
          [0,1,0,0],
          [1,1,0,0],
          [1,0,0,0],
          [1,0,0,1],
          [1,1,0,1]
]  
output = input

mlp = MultiLayerPerceptron.new(input, hidden_layers, output)
mlp.train(200)



