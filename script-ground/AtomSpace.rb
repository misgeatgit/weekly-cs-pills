class Type
end

class MetaData
end
class TruthValue < MetaData
end
class AttentionValue < Metadata
end

class Atom # Allow Atom to have multiple dynamic attributes like TV,AV...
  private
  @type = ""
  @edges = [] # List of unique atom integer ids
  @vertices = [] # List of unique atoms integer ids
  @metadata = [] # Data associated with this atom
  
  public 
  def incoming #edges
  end
  def outgoing #vertices
  end
  def metadata metadata_type
  end
  protected

end

class AtomSpace
  private
  @@next_id = -1
  
  def generate_next_id #static method
      @@next_id = @@next_id + 1
      @@next_id 
  end

  @atom_index = [] # A List lists of atoms. An Index.

  public
  def initialize atomspace = nil
    # This atomspace is a child of atomspace
    if atomspace
      @atom_index = atomspace.get_index # Initialize inde
    end
  end

  def get_index
    @atom_index
  end

  def insert # A map of atoms eg. {AtomX:[{atom1:[{atom11:[..]}],AtomY:[]} 
  end

  def delete # A single atom
  end
end

#---------------------Query-----------------------#

=begin
 -Do template matching of two atoms
=end
class Query 

end

#----------------Storage----------------------------#
# store the atom to disk
# Distributed computing
# 

#----------------Atomese----------------------------#
# Atomese syntax parser.
#
