local snares = {
	"the-open-source-drumkit/snare/snare-bottom-buttend-0-10-3.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend1.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend2.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend3.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend4.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend5.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend6.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend7.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend8.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend9.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend10.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend11.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend12.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend13.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend14.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend15.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend16.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend17.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend18.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend19.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend20.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend21.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend22.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend23.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend24.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend25.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend26.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend27.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend28.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend29.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend30.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend31.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend32.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend33.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend34.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend35.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend36.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend37.wav",
	"the-open-source-drumkit/snare/snare-bottom-buttend38.wav"
}

local snare_sources = {}
for i,v in ipairs(snares) do
	table.insert( snare_sources, love.audio.newSource(v, 'static') )
end

local current_snare = 1

function love.load()
end

function love.update(dt)
end

function love.keypressed(key)
	if (key == 'left') then
		if current_snare > 1 then current_snare = current_snare - 1 end
	end
	if (key == 'right') then
		if current_snare < #snares then current_snare = current_snare + 1 end
	end

	if (key == 'space') then
		-- soundData = love.sound.newSoundData( snares[current_snare] )
		print( snare_sources[current_snare]:getPitch() )

		love.audio.play(snare_sources[current_snare])
	end

	print(current_snare, snares[current_snare] )
end

function love.draw()
end
